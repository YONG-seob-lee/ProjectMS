#include "MS_ModeState_Construct.h"

#include "MS_Define.h"
#include "Controller/MS_PlayerController.h"
#include "Manager_Client/MS_InputManager.h"
#include "Manager_Client/MS_InteractionManager.h"
#include "Prop/MS_Prop.h"


UMS_ModeState_Construct::UMS_ModeState_Construct()
{
}

void UMS_ModeState_Construct::Initialize(uint8 aIndex, const FName& aName)
{
	Super::Initialize(aIndex, aName);
	
	gInteractionMng.OnSelectActorDelegate.AddDynamic(this, &UMS_ModeState_Construct::OnSelectProp);
	gInteractionMng.OnUnselectActorDelegate.AddDynamic(this, &UMS_ModeState_Construct::OnUnselectProp);
}

void UMS_ModeState_Construct::Finalize()
{
	Super::Finalize();

	gInteractionMng.OnUnselectActorDelegate.RemoveDynamic(this, &UMS_ModeState_Construct::OnUnselectProp);
	gInteractionMng.OnSelectActorDelegate.RemoveDynamic(this, &UMS_ModeState_Construct::OnSelectProp);
}

void UMS_ModeState_Construct::Tick(float aDeltaTime)
{
}

void UMS_ModeState_Construct::Begin()
{
	TWeakObjectPtr<AMS_Prop> SelectedProp =  gInteractionMng.GetSelectedActor<AMS_Prop>();
	
	if (SelectedProp != nullptr)
	{
		OnSelectProp(SelectedProp.Get());
	}
}

void UMS_ModeState_Construct::Exit()
{
	UnselectProp();
}

void UMS_ModeState_Construct::OnInputPointerDownEvent(FVector2D aPointerDownPosition, const FHitResult& aInteractableHitResult)
{
	Super::OnInputPointerDownEvent(aPointerDownPosition, aInteractableHitResult);

	AActor* InteractableActor = aInteractableHitResult.GetActor();
	
	if (IsValid(InteractableActor))
	{
		SelectProp(InteractableActor);
	}
}

void UMS_ModeState_Construct::OnInputPointerUpEvent(FVector2D aPointerUpPosition, const FHitResult& aInteractableHitResult)
{
	Super::OnInputPointerUpEvent(aPointerUpPosition, aInteractableHitResult);
}

void UMS_ModeState_Construct::OnInputPointerMove(const FVector2D& aPosition, const FVector2D& aPositionDelta,
	const FVector2D& aPositionDeltaTrend)
{
	Super::OnInputPointerMove(aPosition, aPositionDelta, aPositionDeltaTrend);
}

void UMS_ModeState_Construct::OnInputPointerGlide(const FVector2D& aPosition, const FVector2D& aPositionDelta,
	const FVector2D& aPositionDeltaTrend)
{
	Super::OnInputPointerGlide(aPosition, aPositionDelta, aPositionDeltaTrend);
}

void UMS_ModeState_Construct::OnMouseRightButtonGlide(const FVector2D& aPosition, const FVector2D& aPositionDelta,
	const FVector2D& aPositionDeltaTrend)
{
	Super::OnMouseRightButtonGlide(aPosition, aPositionDelta, aPositionDeltaTrend);
}

void UMS_ModeState_Construct::OnInputPointerHold(float aElapsedTime, const FVector2D& aPosition, const FHitResult& aInteractableHitResult)
{
	Super::OnInputPointerHold(aElapsedTime, aPosition, aInteractableHitResult);

	TWeakObjectPtr<AMS_Prop> SelectedProp =  gInteractionMng.GetSelectedActor<AMS_Prop>();
	
	if (SelectedProp == nullptr)
	{
		return;
	}
	
	if (SelectedProp->GetPropType() == EMS_PropType::Floor || SelectedProp->GetPropType() == EMS_PropType::Wall)
	{
		return;
	}
	
	FHitResult SpaceHitResult = {};
	if (GetHitResultUnderObjectScreenPosition(aPosition, ECollisionChannel::ECC_GameTraceChannel2, false, SpaceHitResult))
	{
		DrawDebugBox(GetWorld(), SpaceHitResult.Location, FVector(10.f), FColor::Yellow, false, 1.f);
		FVector NewObjectLocation = SpaceHitResult.Location;
		MS_LOG_Verbosity(VeryVerbose, TEXT("NewObjectLocation : %f, %f, %f"), NewObjectLocation.X, NewObjectLocation.Y, NewObjectLocation.Z);

		MovePreviewProp(NewObjectLocation);
	}
}

void UMS_ModeState_Construct::OnInputPointerClick(const FVector2D& aPosition, const FHitResult& aInteractableHitResult)
{
	Super::OnInputPointerClick(aPosition, aInteractableHitResult);
}

void UMS_ModeState_Construct::OnPinchAction(float aPinchValue)
{
	Super::OnPinchAction(aPinchValue);
}

void UMS_ModeState_Construct::SelectProp(AActor* ASelectedActor)
{
	gInteractionMng.SelectActor(ASelectedActor);
}

void UMS_ModeState_Construct::UnselectProp()
{
	gInteractionMng.UnselectActor();
}

void UMS_ModeState_Construct::OnSelectProp(AActor* aSelectedActor)
{
	const TObjectPtr<UWorld> World = GetWorld();
	if (!IsValid(World))
	{
		return;
	}

	const TObjectPtr<AMS_PlayerController> PlayerController = World->GetFirstPlayerController<AMS_PlayerController>();
	if (!IsValid(PlayerController))
	{
		return;
	}
	
	if (aSelectedActor == nullptr)
	{
		return;
	}

	if (AMS_Prop* SelectedProp = Cast<AMS_Prop>(aSelectedActor))
	{
		if (SelectedProp->GetPropType() == EMS_PropType::Floor || SelectedProp->GetPropType() == EMS_PropType::Wall)
		{
			return;
		}
		
		// PointerPostionToObjectScreenPositionOffset
		FVector2D PointerScreenPosition = gInputMng.AcquirePointerPositionOnViewport();
		MS_LOG_Verbosity(VeryVerbose, TEXT("OnSelectProp::PointerScreenPosition : %f, %f"), PointerScreenPosition.X, PointerScreenPosition.Y);

		FVector2D ActorCenterScreenPosition;
		GetWorld()->GetFirstPlayerController()->ProjectWorldLocationToScreen(SelectedProp->GetActorLocation(), ActorCenterScreenPosition);
		MS_LOG_Verbosity(VeryVerbose, TEXT("OnSelectProp::ActorCenterScreenPosition : %f, %f"), ActorCenterScreenPosition.X, ActorCenterScreenPosition.Y);
		
		PointerPostionToObjectScreenPositionOffset = ActorCenterScreenPosition - PointerScreenPosition;
		MS_LOG_Verbosity(VeryVerbose, TEXT("OnSelectProp::ClickPositionToObjectScreenPositionOffset : %f, %f"), PointerPostionToObjectScreenPositionOffset.X, PointerPostionToObjectScreenPositionOffset.Y);

		// PreviewProp
		CreatePreviewProp(SelectedProp);
	}
}

void UMS_ModeState_Construct::OnUnselectProp(AActor* aUnselectedActor)
{
	if (aUnselectedActor != nullptr)
	{
		if (AMS_Prop* UnselectedProp = Cast<AMS_Prop>(aUnselectedActor))
		{
			if (UnselectedProp->GetPropType() == EMS_PropType::Floor || UnselectedProp->GetPropType() == EMS_PropType::Wall)
			{
				return;
			}

			CancelPreviewProp(UnselectedProp);
		}
	}
}

void UMS_ModeState_Construct::CreatePreviewProp(AMS_Prop* aSelectedProp)
{
	const TObjectPtr<UWorld> World = GetWorld();
	if (!IsValid(World))
	{
		return;
	}

	if (IsValid(SelectedPreviewProp))
	{
		CancelPreviewProp(SelectedPreviewProp->GetLinkedProp().Get());
	}
	
	aSelectedProp->SetActorHiddenInGame(true);
		
	FVector Location = aSelectedProp->GetActorLocation() + FVector(0.f, 0.f, 10.f);
	FRotator Rotator = aSelectedProp->GetActorRotation();
	SelectedPreviewProp = World->SpawnActor<AMS_Prop>(aSelectedProp->GetClass(), Location, Rotator);
	SelectedPreviewProp->InitializeWhenPreviewProp(aSelectedProp);

	SelectedPreviewProp->SetActorEnableCollision(false);
}

void UMS_ModeState_Construct::MovePreviewProp(const FVector& NewLocation)
{
	SelectedPreviewProp->SetActorLocation(NewLocation + FVector(0.f, 0.f, 10.f));
}

void UMS_ModeState_Construct::ApplyPreviewProp()
{
}

void UMS_ModeState_Construct::CancelPreviewProp(AMS_Prop* aSelectedProp)
{
	aSelectedProp->SetActorHiddenInGame(false);
	SelectedPreviewProp->Destroy();
}

bool UMS_ModeState_Construct::GetHitResultUnderObjectScreenPosition(const FVector2D& aPointerPostion,
	ECollisionChannel TraceChannel, bool bTraceComplex, FHitResult& HitResult) const
{
	const TObjectPtr<UWorld> World = GetWorld();
	if (!IsValid(World))
	{
		return false;
	}

	const TObjectPtr<AMS_PlayerController> PlayerController = World->GetFirstPlayerController<AMS_PlayerController>();
	if (!IsValid(PlayerController))
	{
		return false;
	}

	MS_LOG_Verbosity(VeryVerbose, TEXT("PlayerController::aPointerPostion : %f, %f"), aPointerPostion.X, aPointerPostion.Y);

	MS_LOG_Verbosity(VeryVerbose, TEXT("PlayerController::PointerPostionToObjectScreenPositionOffset : %f, %f"), PointerPostionToObjectScreenPositionOffset.X, PointerPostionToObjectScreenPositionOffset.Y);

	FVector2D ScreenPosition = aPointerPostion + PointerPostionToObjectScreenPositionOffset;
	MS_LOG_Verbosity(VeryVerbose, TEXT("PlayerController::ScreenPosition : %f, %f"), ScreenPosition.X, ScreenPosition.Y);
		
	return PlayerController->GetHitResultAtScreenPosition(ScreenPosition, TraceChannel, bTraceComplex, HitResult);
}
