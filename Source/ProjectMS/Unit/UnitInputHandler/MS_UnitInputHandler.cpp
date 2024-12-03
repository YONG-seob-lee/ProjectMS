#include "Unit/UnitInputHandler/MS_UnitInputHandler.h"

#include "Kismet/GameplayStatics.h"
#if WITH_EDITOR
#include "LevelEditor.h"
#include "IAssetViewport.h"
#endif

#include "CoreClass/Controller/MS_PlayerController.h"

UMS_UnitInputHandler::UMS_UnitInputHandler()
{
}

void UMS_UnitInputHandler::BindController(AMS_PlayerController* aPlayerController)
{
	PlayerControllerInst = aPlayerController;
}

void UMS_UnitInputHandler::HandleMouseLeftButtonDown()
{
	if (MouseLeftButtonPressFlag == false)
	{
		MouseLeftButtonPressFlag = true;
		HandlePointerDown();
	}
}

void UMS_UnitInputHandler::HandleMouseLeftButtonUp()
{
	if (MouseLeftButtonPressFlag == true)
	{
		MouseLeftButtonPressFlag = false;
		HandlePointerUp();
	}
}

void UMS_UnitInputHandler::HandleMouseRightButtonDown()
{
	if (MouseRightButtonPressFlag == false)
	{
		MouseRightButtonPressFlag = true;
	}
}

void UMS_UnitInputHandler::HandleMouseRightButtonUp()
{
	if (MouseRightButtonPressFlag == true)
	{
		MouseRightButtonPressFlag = false;
	}
}

void UMS_UnitInputHandler::HandleTouchDown(ETouchIndex::Type aFingerIndex, FVector aLocation)
{
	if (aFingerIndex == ETouchIndex::Touch1 && TouchPressFlag == false)
	{
		UKismetSystemLibrary::PrintString(GetWorld(), TEXT("HandleTouchDown"));
		TouchPressFlag = true;
		HandlePointerDown();
	}
}

void UMS_UnitInputHandler::HandleTouchUp(ETouchIndex::Type aFingerIndex, FVector aLocation)
{
	if (aFingerIndex == ETouchIndex::Touch1 && TouchPressFlag == true)
	{
		UKismetSystemLibrary::PrintString(GetWorld(), TEXT("HandleTouchUp"));
		TouchPressFlag = false;
		HandlePointerUp();
	}
}

void UMS_UnitInputHandler::HandlePointerDown()
{
	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("HandlePointerDown"));
	PointerDownTimestamp = FDateTime::UtcNow().GetTicks();
#if PLATFORM_WINDOWS || PLATFORM_MAC
	PointerDownPosition = PlayerControllerInst->AcquireMousePositionOnViewport();
#elif PLATFORM_ANDROID || PLATFORM_IOS
	PointerDownPosition = AcquireTouchPositionOnViewport(ETouchIndex::Touch1);
#endif

	FHitResult HitResult = {};
	if (PlayerControllerInst->GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel1, false, HitResult) == true)
		PointerDownActor = HitResult.GetActor();
	else
		PointerDownActor = nullptr;

	OnPointerDownDelegate.Broadcast(PointerDownPosition, PointerDownActor);

	PointerDragStartPosition.X = PointerDragStartPosition.Y = PointerDragEndPosition.X = PointerDragEndPosition.Y = -FLT_MAX;
	GetWorld()->GetTimerManager().SetTimer(HandlePointerDragTimerHandle, this, &UMS_UnitInputHandler::HandlePointerDrag, 0.025f, true);
	GetWorld()->GetTimerManager().SetTimer(HandlePointerHoldTimerHandle, this, &UMS_UnitInputHandler::HandlePointerHold, POINTER_HOLD_DELAY);
}

void UMS_UnitInputHandler::HandlePointerUp()
{
	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("HandlePointerUp"));
	PointerUpTimestamp = FDateTime::UtcNow().GetTicks();
#if PLATFORM_WINDOWS || PLATFORM_MAC
	PointerUpPosition = PlayerControllerInst->AcquireMousePositionOnViewport();
#elif PLATFORM_ANDROID || PLATFORM_IOS
	PointerUpPosition = AcquireTouchPositionOnViewport(ETouchIndex::Touch1);
#endif

	FHitResult HitResult = {};
	if (PlayerControllerInst->GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel1, false, HitResult) == true)
		PointerUpActor = HitResult.GetActor();
	else
		PointerUpActor = nullptr;

	OnPointerUpDelegate.Broadcast(PointerUpPosition, PointerUpActor);

	PointerDragFlag = false;
	GetWorld()->GetTimerManager().ClearTimer(HandlePointerDragTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(HandlePointerHoldTimerHandle);
	PointerDownUpIntervalTime = (PointerUpTimestamp - PointerDownTimestamp) / 10000000.0f;

	HandlePointerClick();
}

void UMS_UnitInputHandler::HandlePointerMove()
{
	FVector2D PreviousPointerMovePosition = PointerMovePosition;
#if PLATFORM_WINDOWS || PLATFORM_MAC
	PointerMovePosition = PlayerControllerInst->AcquireMousePositionOnViewport();
#elif PLATFORM_ANDROID || PLATFORM_IOS
	PointerMovePosition = AcquireTouchPositionOnViewport(ETouchIndex::Touch1);
#endif
	if (PreviousPointerMovePosition.Equals(FVector2D(-FLT_MAX, -FLT_MAX)) == true)
		PointerMovePositionDelta = FVector2D::ZeroVector;
	else
		PointerMovePositionDelta = PointerMovePosition - PreviousPointerMovePosition;

	PointerMovePositionDeltaArray.Add(PointerMovePositionDelta);
	if (PointerMovePositionDeltaArray.Num() > 5)
		PointerMovePositionDeltaArray.RemoveAt(0, EAllowShrinking::Yes);

	PointerMovePositionDeltaTrend = FVector2D::ZeroVector;
	for (int i = 0; i < PointerMovePositionDeltaArray.Num(); ++i)
		PointerMovePositionDeltaTrend += PointerMovePositionDeltaArray[i];
	PointerMovePositionDeltaTrend /= PointerMovePositionDeltaArray.Num();

	OnPointerMoveDelegate.Broadcast(PointerMovePosition, PointerMovePositionDelta, PointerMovePositionDeltaTrend);

	HandlePointerGlide();
}

void UMS_UnitInputHandler::HandlePointerHover()
{
	FHitResult HitResult = {};
	if (PlayerControllerInst->GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel1, false, HitResult) == false)
	{
		if (PointerHoverActor != nullptr)
		{
#if PLATFORM_WINDOWS || PLATFORM_MAC
			PointerHoverPosition = PlayerControllerInst->AcquireMousePositionOnViewport();
#elif PLATFORM_ANDROID || PLATFORM_IOS
			PointerHoverPosition = AcquireTouchPositionOnViewport(ETouchIndex::Touch1);
#endif

			OnPointerHoverLeaveDelegate.Broadcast(PointerHoverPosition, PointerHoverActor);
			PointerHoverActor = nullptr;
		}

		return;
	}
	else if (PointerHoverActor == HitResult.GetActor())
	{
#if PLATFORM_WINDOWS || PLATFORM_MAC
		PointerHoverPosition = PlayerControllerInst->AcquireMousePositionOnViewport();
#elif PLATFORM_ANDROID || PLATFORM_IOS
		PointerHoverPosition = AcquireTouchPositionOnViewport(ETouchIndex::Touch1);
#endif

		OnPointerHoverDelegate.Broadcast(PointerHoverPosition, PointerHoverActor);

		return;
	}

#if PLATFORM_WINDOWS || PLATFORM_MAC
	PointerHoverPosition = PlayerControllerInst->AcquireMousePositionOnViewport();
#elif PLATFORM_ANDROID || PLATFORM_IOS
	PointerHoverPosition = AcquireTouchPositionOnViewport(ETouchIndex::Touch1);
#endif

	if (PointerHoverActor != nullptr)
		OnPointerHoverLeaveDelegate.Broadcast(PointerHoverPosition, PointerHoverActor);
	PointerHoverActor = HitResult.GetActor();
	OnPointerHoverEnterDelegate.Broadcast(PointerHoverPosition, PointerHoverActor);
}

void UMS_UnitInputHandler::HandlePointerGlide()
{
	if (MouseLeftButtonPressFlag == true || TouchPressFlag == true)
	{
		FVector2D PreviousPointerGlidePosition = PointerGlidePosition;
		PointerGlidePosition = PointerMovePosition;
		if (PreviousPointerGlidePosition.Equals(FVector2D(-FLT_MAX, -FLT_MAX)) == true)
			PointerGlidePositionDelta = FVector2D::ZeroVector;
		else
			PointerGlidePositionDelta = PointerGlidePosition - PreviousPointerGlidePosition;

		PointerGlidePositionDeltaArray.Add(PointerGlidePositionDelta);
		if (PointerGlidePositionDeltaArray.Num() > 5)
			PointerGlidePositionDeltaArray.RemoveAt(0, EAllowShrinking::Yes);

		PointerGlidePositionDeltaTrend = FVector2D::ZeroVector;
		for (int i = 0; i < PointerGlidePositionDeltaArray.Num(); ++i)
			PointerGlidePositionDeltaTrend += PointerGlidePositionDeltaArray[i];
		PointerGlidePositionDeltaTrend /= PointerMovePositionDeltaArray.Num();
		OnPointerGlideDelegate.Broadcast(PointerGlidePosition, PointerGlidePositionDelta, PointerGlidePositionDeltaTrend);
	}
	else
	{
		PointerGlidePosition = { -FLT_MAX, -FLT_MAX };
		PointerGlidePositionDelta = { -FLT_MAX, -FLT_MAX };
		PointerGlidePositionDeltaArray.Empty();
		PointerGlidePositionDeltaTrend = { -FLT_MAX, -FLT_MAX };
	}
}

void UMS_UnitInputHandler::HandlePointerDrag()
{
	if (PointerDragFlag == false)
		PointerDragFlag = true;
	if (PointerDragStartPosition.Equals(FVector2D(-FLT_MAX, -FLT_MAX)) == true)
#if PLATFORM_WINDOWS || PLATFORM_MAC
		PointerDragStartPosition = PlayerControllerInst->AcquireMousePositionOnViewport();
#elif PLATFORM_ANDROID || PLATFORM_IOS
		PointerDragStartPosition = AcquireTouchPositionOnViewport(ETouchIndex::Touch1);
#endif
#if PLATFORM_WINDOWS || PLATFORM_MAC
	PointerDragEndPosition = PlayerControllerInst->AcquireMousePositionOnViewport();
#elif PLATFORM_ANDROID || PLATFORM_IOS
	PointerDragEndPosition = AcquireTouchPositionOnViewport(ETouchIndex::Touch1);
#endif

	TArray<AActor*> AllActorArray = {};
	FBox2D DragAreaPosition(FVector2D(FMath::Min(PointerDragStartPosition.X, PointerDragEndPosition.X), FMath::Min(PointerDragStartPosition.Y, PointerDragEndPosition.Y)), FVector2D(FMath::Max(PointerDragStartPosition.X, PointerDragEndPosition.X), FMath::Max(PointerDragStartPosition.Y, PointerDragEndPosition.Y)));
	FVector2D ActorProjectedPosition = {};
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), AllActorArray);
	PointerDragActorArray.Empty();
	for (int i = 0; i < AllActorArray.Num(); ++i)
	{
		bool ProjectionResult = PlayerControllerInst->ProjectWorldLocationToScreen(AllActorArray[i]->GetActorLocation(), ActorProjectedPosition);
		if (ProjectionResult == true &&
			ActorProjectedPosition.X >= DragAreaPosition.Min.X && ActorProjectedPosition.X <= DragAreaPosition.Max.X &&
			ActorProjectedPosition.Y >= DragAreaPosition.Min.Y && ActorProjectedPosition.Y <= DragAreaPosition.Max.Y &&
			AllActorArray[i]->GetComponentsCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1) == ECollisionResponse::ECR_Block)
		{
			PointerDragActorArray.Add(AllActorArray[i]);
		}
	}

	OnPointerDragDelegate.Broadcast(PointerDragStartPosition, PointerDragEndPosition, PointerDragActorArray);
}

void UMS_UnitInputHandler::HandlePointerHold()
{
#if PLATFORM_WINDOWS || PLATFORM_MAC
	PointerHoldPosition = PlayerControllerInst->AcquireMousePositionOnViewport();
#elif PLATFORM_ANDROID || PLATFORM_IOS
	PointerHoldPosition = AcquireTouchPositionOnViewport(ETouchIndex::Touch1);
#endif

	FHitResult HitResult = {};
	if (PlayerControllerInst->GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel1, false, HitResult) == true)
		PointerHoldActor = HitResult.GetActor();
	else
		PointerHoldActor = nullptr;

	OnPointerHoldDelegate.Broadcast(PointerHoldPosition, PointerHoldActor);
	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("HandlePointerHold"));
}

void UMS_UnitInputHandler::HandlePointerClick()
{
	if (PointerDownUpIntervalTime < POINTER_CLICK_DELAY)
	{
		PointerClickIntervalTime = (FDateTime::UtcNow().GetTicks() - PointerClickTimestamp) / 10000000.0f;;
		PointerClickTimestamp = FDateTime::UtcNow().GetTicks();
#if PLATFORM_WINDOWS || PLATFORM_MAC
		PointerClickPosition = PlayerControllerInst->AcquireMousePositionOnViewport();
#elif PLATFORM_ANDROID || PLATFORM_IOS
		PointerClickPosition = AcquireTouchPositionOnViewport(ETouchIndex::Touch1);
#endif

		if (PointerDownActor != nullptr && PointerUpActor != nullptr && PointerDownActor == PointerUpActor)
		{
			PointerClickActor = PointerUpActor;
		}
		else
		{
			PointerClickActor = nullptr;
		}

		OnPointerClickDelegate.Broadcast(PointerClickPosition, PointerClickActor);
		UKismetSystemLibrary::PrintString(GetWorld(), TEXT("HandlePointerClick"));

		HandlePointerDoubleClick();
	}
}

void UMS_UnitInputHandler::HandlePointerDoubleClick()
{
	if (PointerClickIntervalTime < POINTER_DOUBLE_CLICK_DELAY)
	{
#if PLATFORM_WINDOWS || PLATFORM_MAC
		PointerDoubleClickPosition = PlayerControllerInst->AcquireMousePositionOnViewport();
#elif PLATFORM_ANDROID || PLATFORM_IOS
		PointerDoubleClickPosition = AcquireTouchPositionOnViewport(ETouchIndex::Touch1);
#endif

		OnPointerDoubleClickDelegate.Broadcast(PointerDoubleClickPosition, PointerDoubleClickActor);
		UKismetSystemLibrary::PrintString(GetWorld(), TEXT("HandlePointerDoubleClick"));
	}
}