#include "MS_PlayerController.h"

#include "Kismet/GameplayStatics.h"
#if WITH_EDITOR
#include "LevelEditor.h"
#include "IAssetViewport.h"
#endif

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

#include "Management/MS_UnitManager.h"
#include "Management/MS_PlayerCameraManager.h"

#include "Unit/UnitState/MS_UnitStateBase.h"

AMS_PlayerController::AMS_PlayerController()
{
	PlayerCameraManagerClass = AMS_PlayerCameraManager::StaticClass();

	PrimaryActorTick.bCanEverTick = true;
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	bEnableMouseOverEvents = true;
	bEnableTouchOverEvents = true;

	static ConstructorHelpers::FObjectFinder<UInputMappingContext> MappingContextFinder(TEXT("/Game/Input/MappingContext/CameraInputMappingContext"));
	MS_CHECK(MappingContextFinder.Object);
	MappingContext = MappingContextFinder.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> PinchInputActionFinder(TEXT("/Game/Input/InputAction/PinchInputAction"));
	MS_CHECK(PinchInputActionFinder.Object);
	PinchInputAction = PinchInputActionFinder.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> PointerPressInputActionFinder(TEXT("/Game/Input/InputAction/PointerPressInputAction"));
	MS_CHECK(PointerPressInputActionFinder.Object);
	PointerPressInputAction = PointerPressInputActionFinder.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> RotationInputActionFinder(TEXT("/Game/Input/InputAction/RotateInputAction"));
	MS_CHECK(RotationInputActionFinder.Object);
	RotationInputAction = RotationInputActionFinder.Object;
}

void AMS_PlayerController::RegisterManagement()
{
	// BeginPlay
	if(Management)
	{
		return;
	}
	
	Management = NewObject<UMS_Management>(this);
	MS_CHECK(Management);
	Management->InitManager();
}


void AMS_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(HandlePointerMoveTimerHandle, this, &AMS_PlayerController::HandlePointerMove, 0.01f, true);

	RegisterManagement();
}

void AMS_PlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearTimer(HandlePointerMoveTimerHandle);
}

void AMS_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	MS_CHECK(EnhancedInputLocalPlayerSubSystem);
	EnhancedInputLocalPlayerSubSystem->AddMappingContext(MappingContext, 0);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	MS_CHECK(EnhancedInputComponent);

	EnhancedInputComponent->BindAction(PointerPressInputAction, ETriggerEvent::Started, this, TEXT("HandlePointerDown"));
	EnhancedInputComponent->BindAction(PointerPressInputAction, ETriggerEvent::Completed, this, TEXT("HandlePointerUp"));
	EnhancedInputComponent->BindAction(PinchInputAction, ETriggerEvent::Started, this, TEXT("HandlePinchAction"));

	// DEBUG
	EnhancedInputComponent->BindAction(RotationInputAction, ETriggerEvent::Started, this, TEXT("HandleMouseRightButtonDown"));
	EnhancedInputComponent->BindAction(RotationInputAction, ETriggerEvent::Completed, this, TEXT("HandleMouseRightButtonUp"));
}

FVector2D AMS_PlayerController::AcquirePointerPositionOnViewport()
{
	FVector2D PointerPosition = {};

#if PLATFORM_WINDOWS || PLATFORM_MAC
	GetMousePosition(PointerPosition.X, PointerPosition.Y);

#elif PLATFORM_ANDROID || PLATFORM_IOS
	bool CurrentlyTouchPressFlag = {};
	GetInputTouchState(ETouchIndex::Touch1, PointerPosition.X, PointerPosition.Y, CurrentlyTouchPressFlag);
#endif
	return PointerPosition;
}

void AMS_PlayerController::HandlePointerDown(const FInputActionValue& aValue)
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

	GetWorld()->GetTimerManager().SetTimer(HandlePointerHoldTimerHandle, this, &AMS_PlayerController::HandlePointerHold, POINTER_HOLD_DELAY);
}

void AMS_PlayerController::HandlePointerUp(const FInputActionValue& aValue)
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
	PointerDownUpIntervalTime = (PointerUpTimestamp - PointerDownTimestamp) / 10000000.0f;

	HandlePointerClick();
}

void AMS_PlayerController::HandlePointerClick()
{
	if (PointerDownUpIntervalTime < POINTER_CLICK_DELAY)
	{
		PointerClickIntervalTime = (FDateTime::UtcNow().GetTicks() - PointerClickTimestamp) / 10000000.0f;;
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

void AMS_PlayerController::HandlePointerMove()
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
	if (PointerMovePositionDeltaArray.Num() > 5)
	{
		PointerMovePositionDeltaArray.RemoveAt(0, EAllowShrinking::Yes);
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

void AMS_PlayerController::HandlePointerGlide()
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
		if (PointerGlidePositionDeltaArray.Num() > 5)
		{
			PointerGlidePositionDeltaArray.RemoveAt(0, EAllowShrinking::Yes);
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

// DEBUG
void AMS_PlayerController::HandleMouseRightButtonDown(const FInputActionValue& aValue)
{
	if (MouseRightButtonPressFlag == true)
	{
		return;
	}
	MouseRightButtonPressFlag = true;
}

void AMS_PlayerController::HandleMouseRightButtonUp(const FInputActionValue& aValue)
{
	if (MouseRightButtonPressFlag == false)
	{
		return;
	}
	MouseRightButtonPressFlag = false;
}

void AMS_PlayerController::HandlePinchAction(const FInputActionValue& aValue)
{
	OnPinchActionDelegate.Broadcast(aValue.Get<float>());
}

void AMS_PlayerController::HandlePointerHold()
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

void AMS_PlayerController::PostLoad()
{
	Super::PostLoad();
}

TObjectPtr<AMS_CharacterBase> AMS_PlayerController::GetCharacterBase() const
{
	MS_CHECK(UnitBase);

	return UnitBase->GetCharacterBase();
}

void AMS_PlayerController::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
}

