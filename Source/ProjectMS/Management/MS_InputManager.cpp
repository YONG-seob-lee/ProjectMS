// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_InputManager.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputActionValue.h"
#include "MS_Define.h"
#include "Controller/MS_PlayerController.h"
#include "Table/Caches/MS_CommonCacheTable.h"

namespace InputInstancePath
{
	const FString MappingContextPath = TEXT("/Game/Input/MappingContext/CameraInputMappingContext");
	const FString PinchInputAction = TEXT("/Game/Input/InputAction/PinchInputAction");
	const FString PointerPressInputAction = TEXT("/Game/Input/InputAction/PointerPressInputAction");
	const FString RotationInputActionFinder = TEXT("/Game/Input/InputAction/RotateInputAction");
}

namespace InputPriority
{
	constexpr int32 First = 0;
}

namespace PointerParameter
{
	constexpr int32 ArrayFirst = 0;
	constexpr int32 MoveDeltaArrayMax = 5;
}

namespace IntervalTimeValue
{
	constexpr double Separation = 10000000.f; 
}

UMS_InputManager::UMS_InputManager()
{
	InputManager = this;

	static ConstructorHelpers::FObjectFinder<UInputMappingContext> MappingContextFinder(*InputInstancePath::MappingContextPath);
	MS_CHECK(MappingContextFinder.Object);
	MappingContext = MappingContextFinder.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> PinchInputActionFinder(*InputInstancePath::PinchInputAction);
	MS_CHECK(PinchInputActionFinder.Object);
	PinchInputAction = PinchInputActionFinder.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> PointerPressInputActionFinder(*InputInstancePath::PointerPressInputAction);
	MS_CHECK(PointerPressInputActionFinder.Object);
	PointerPressInputAction = PointerPressInputActionFinder.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> RotationInputActionFinder(*InputInstancePath::RotationInputActionFinder);
	MS_CHECK(RotationInputActionFinder.Object);
	RotationInputAction = RotationInputActionFinder.Object;
}

void UMS_InputManager::Initialize()
{
	Super::Initialize();

	GetWorld()->GetTimerManager().SetTimer(HandlePointerMoveTimerHandle, this, &UMS_InputManager::HandlePointerMove, 0.01f, true);
}

void UMS_InputManager::Finalize()
{
	GetWorld()->GetTimerManager().ClearTimer(HandlePointerMoveTimerHandle);
	
	Super::Finalize();
}

void UMS_InputManager::SetupInputComponent(const TObjectPtr<UInputComponent>& aInputComponent, const TObjectPtr<ULocalPlayer>& aLocalPlayer)
{
	UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(aLocalPlayer);
	MS_CHECK(EnhancedInputLocalPlayerSubSystem);
	EnhancedInputLocalPlayerSubSystem->AddMappingContext(MappingContext, InputPriority::First);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(aInputComponent);
	MS_CHECK(EnhancedInputComponent);

	EnhancedInputComponent->BindAction(PointerPressInputAction, ETriggerEvent::Started, this, TEXT("HandlePointerDown"));
	EnhancedInputComponent->BindAction(PointerPressInputAction, ETriggerEvent::Completed, this, TEXT("HandlePointerUp"));
	EnhancedInputComponent->BindAction(PinchInputAction, ETriggerEvent::Started, this, TEXT("HandlePinchAction"));

	// DEBUG
	EnhancedInputComponent->BindAction(RotationInputAction, ETriggerEvent::Started, this, TEXT("HandleMouseRightButtonDown"));
	EnhancedInputComponent->BindAction(RotationInputAction, ETriggerEvent::Completed, this, TEXT("HandleMouseRightButtonUp"));
}

FVector2D UMS_InputManager::AcquirePointerPositionOnViewport() const
{
	FVector2D PointerPosition = {};

#if PLATFORM_WINDOWS || PLATFORM_MAC
	const TObjectPtr<UWorld> World = GetWorld();
	MS_CHECK(World);

	const TObjectPtr<AMS_PlayerController> PlayerController = World->GetFirstPlayerController<AMS_PlayerController>();
	MS_CHECK(PlayerController);

	PlayerController->GetMousePosition(PointerPosition.X, PointerPosition.Y);
	
#elif PLATFORM_ANDROID || PLATFORM_IOS
	bool CurrentlyTouchPressFlag = {};
	GetInputTouchState(ETouchIndex::Touch1, PointerPosition.X, PointerPosition.Y, CurrentlyTouchPressFlag);
#endif
	return PointerPosition;
}

void UMS_InputManager::HandlePointerDown(const FInputActionValue& aValue)
{
	if (PointerPressFlag == true)
	{
		return;
	}
	PointerPressFlag = true;

	PointerDownTimestamp = FDateTime::UtcNow().GetTicks();
	PointerDownPosition = AcquirePointerPositionOnViewport();

	FHitResult HitResult = {};
	if (GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel1, false, HitResult) == true)
	{
		PointerDownActor = HitResult.GetActor();
	}
	else
	{
		PointerDownActor = nullptr;
	}

	OnPointerDownDelegate.Broadcast(PointerDownPosition, PointerDownActor);

	const TObjectPtr<UMS_CommonCacheTable> CommonTable = Cast<UMS_CommonCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::Common));
	MS_CHECK(CommonTable);
	
	GetWorld()->GetTimerManager().SetTimer(HandlePointerHoldTimerHandle, this, &UMS_InputManager::HandlePointerHold, CommonTable->GetParameter02(CommonContents::POINTER_HOLD_DELAY));
}

void UMS_InputManager::HandlePointerUp(const FInputActionValue& aValue)
{
	if (PointerPressFlag == false)
	{
		return;
	}
	PointerPressFlag = false;

	PointerUpTimestamp = FDateTime::UtcNow().GetTicks();
	PointerUpPosition = AcquirePointerPositionOnViewport();

	FHitResult HitResult = {};
	if (GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel1, false, HitResult) == true)
	{
		PointerUpActor = HitResult.GetActor();
	}
	else
	{
		PointerUpActor = nullptr;
	}

	OnPointerUpDelegate.Broadcast(PointerUpPosition, PointerUpActor);

	GetWorld()->GetTimerManager().ClearTimer(HandlePointerHoldTimerHandle);
	PointerDownUpIntervalTime = (PointerUpTimestamp - PointerDownTimestamp) / IntervalTimeValue::Separation;

	HandlePointerClick();
}

void UMS_InputManager::HandlePointerHold()
{
	PointerHoldPosition = AcquirePointerPositionOnViewport();

	FHitResult HitResult = {};
	if (GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel1, false, HitResult) == true)
	{
		if (PointerDownActor != nullptr && PointerDownActor == HitResult.GetActor())
		{
			PointerHoldActor = HitResult.GetActor();
		}
	}
	else
	{
		PointerHoldActor = nullptr;
	}

	OnPointerHoldDelegate.Broadcast(PointerHoldPosition, PointerHoldActor);
}

void UMS_InputManager::HandlePointerClick()
{
	const TObjectPtr<UMS_CommonCacheTable> CommonTable = Cast<UMS_CommonCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::Common));
	MS_CHECK(CommonTable);
	
	if (PointerDownUpIntervalTime < CommonTable->GetParameter02(CommonContents::POINTER_CLICK_DELAY))
	{
		PointerClickIntervalTime = (FDateTime::UtcNow().GetTicks() - PointerClickTimestamp) / IntervalTimeValue::Separation;
		PointerClickTimestamp = FDateTime::UtcNow().GetTicks();
		PointerClickPosition = AcquirePointerPositionOnViewport();

		if (PointerDownActor != nullptr && PointerUpActor != nullptr && PointerDownActor == PointerUpActor)
		{
			PointerClickActor = PointerUpActor;
		}
		else
		{
			PointerClickActor = nullptr;
		}

		OnPointerClickDelegate.Broadcast(PointerClickPosition, PointerClickActor);
	}
}

void UMS_InputManager::HandlePointerMove()
{
	FVector2D PreviousPointerMovePosition = PointerMovePosition;
	PointerMovePosition = AcquirePointerPositionOnViewport();

	if (PreviousPointerMovePosition.Equals(FVector2D(-FLT_MAX, -FLT_MAX)) == true)
	{
		PointerMovePositionDelta = FVector2D::ZeroVector;
	}
	else
	{
		PointerMovePositionDelta = PointerMovePosition - PreviousPointerMovePosition;
	}

	PointerMovePositionDeltaArray.Add(PointerMovePositionDelta);
	if (PointerMovePositionDeltaArray.Num() > PointerParameter::MoveDeltaArrayMax)
	{
		PointerMovePositionDeltaArray.RemoveAt(PointerParameter::ArrayFirst, EAllowShrinking::Yes);
	}

	PointerMovePositionDeltaTrend = FVector2D::ZeroVector;
	for (int i = 0; i < PointerMovePositionDeltaArray.Num(); ++i)
	{
		PointerMovePositionDeltaTrend += PointerMovePositionDeltaArray[i];
	}
	PointerMovePositionDeltaTrend /= PointerMovePositionDeltaArray.Num();

	OnPointerMoveDelegate.Broadcast(PointerMovePosition, PointerMovePositionDelta, PointerMovePositionDeltaTrend);
	
	HandlePointerGlide();
}

void UMS_InputManager::HandlePointerGlide()
{
	// DEBUG
	if (PointerPressFlag == true || MouseRightButtonPressFlag == true)
	{
		FVector2D PreviousPointerGlidePosition = PointerGlidePosition;
		PointerGlidePosition = PointerMovePosition;
		if (PreviousPointerGlidePosition.Equals(FVector2D(-FLT_MAX, -FLT_MAX)) == true)
		{
			PointerGlidePositionDelta = FVector2D::ZeroVector;
		}
		else
		{
			PointerGlidePositionDelta = PointerGlidePosition - PreviousPointerGlidePosition;
		}

		PointerGlidePositionDeltaArray.Add(PointerGlidePositionDelta);
		if (PointerGlidePositionDeltaArray.Num() > PointerParameter::MoveDeltaArrayMax)
		{
			PointerGlidePositionDeltaArray.RemoveAt(PointerParameter::ArrayFirst, EAllowShrinking::Yes);
		}

		PointerGlidePositionDeltaTrend = FVector2D::ZeroVector;
		for (int i = 0; i < PointerGlidePositionDeltaArray.Num(); ++i)
		{
			PointerGlidePositionDeltaTrend += PointerGlidePositionDeltaArray[i];
		}
		PointerGlidePositionDeltaTrend /= PointerMovePositionDeltaArray.Num();

		if (PointerPressFlag == true)
		{
			OnPointerGlideDelegate.Broadcast(PointerGlidePosition, PointerGlidePositionDelta, PointerGlidePositionDeltaTrend);
		}

		// DEBUG
		if (MouseRightButtonPressFlag == true)
		{
			OnMouseRightButtonGlideDelegate.Broadcast(PointerGlidePosition, PointerGlidePositionDelta, PointerGlidePositionDeltaTrend);
		}
	}
	else
	{
		PointerGlidePosition = { -FLT_MAX, -FLT_MAX };
		PointerGlidePositionDelta = { -FLT_MAX, -FLT_MAX };
		PointerGlidePositionDeltaArray.Empty();
		PointerGlidePositionDeltaTrend = { -FLT_MAX, -FLT_MAX };
	}
}

void UMS_InputManager::HandlePinchAction(const FInputActionValue& aValue)
{
	OnPinchActionDelegate.Broadcast(aValue.Get<float>());
}

void UMS_InputManager::HandleMouseRightButtonDown(const FInputActionValue& aValue)
{
	if (MouseRightButtonPressFlag == true)
	{
		return;
	}
	MouseRightButtonPressFlag = true;
}

void UMS_InputManager::HandleMouseRightButtonUp(const FInputActionValue& aValue)
{
	if (MouseRightButtonPressFlag == false)
	{
		return;
	}
	MouseRightButtonPressFlag = false;
}

bool UMS_InputManager::GetHitResultUnderCursor(ECollisionChannel TraceChannel, bool bTraceComplex, FHitResult& HitResult) const
{
	const TObjectPtr<UWorld> World = GetWorld();
	MS_CHECK(World);

	const TObjectPtr<AMS_PlayerController> PlayerController = World->GetFirstPlayerController<AMS_PlayerController>();
	MS_CHECK(PlayerController);

	return PlayerController->GetHitResultUnderCursor(TraceChannel, bTraceComplex, HitResult);
}

UMS_InputManager* UMS_InputManager::GetInstance()
{
	return InputManager;
}
