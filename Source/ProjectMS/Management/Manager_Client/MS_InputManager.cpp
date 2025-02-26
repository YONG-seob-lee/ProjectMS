// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_InputManager.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputActionValue.h"
#include "MS_Define.h"
#include "MS_ModeManager.h"
#include "MS_WidgetManager.h"
#include "Controller/MS_PlayerController.h"
#include "Mode/ModeState/MS_ModeStateBase.h"

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

	TouchInputProcessor = MakeShareable(new IMS_TouchInputProcessor());
	FSlateApplication::Get().RegisterInputPreProcessor(TouchInputProcessor);
	TouchInputProcessor->Initialize();
	
}

void UMS_InputManager::Finalize()
{
	FSlateApplication::Get().UnregisterInputPreProcessor(TouchInputProcessor);
	TouchInputProcessor->Finalize();
	
	Super::Finalize();
}

void UMS_InputManager::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);

	if (PointerPressFlag == true || MouseRightButtonPressFlag == true)
	{
		ElapsedHoldTime += aDeltaTime;
	}
}

void UMS_InputManager::SetupInputComponent(const TObjectPtr<UInputComponent>& aInputComponent, const TObjectPtr<ULocalPlayer>& aLocalPlayer)
{
	UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(aLocalPlayer);
	MS_CHECK(EnhancedInputLocalPlayerSubSystem);
	EnhancedInputLocalPlayerSubSystem->AddMappingContext(MappingContext, InputPriority::First);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(aInputComponent);
	MS_CHECK(EnhancedInputComponent);

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
	const TObjectPtr<UWorld> World = GetWorld();
	MS_CHECK(World);
	const TObjectPtr<AMS_PlayerController> PlayerController = World->GetFirstPlayerController<AMS_PlayerController>();
	MS_CHECK(PlayerController);
	PlayerController->GetInputTouchState(ETouchIndex::Touch1, PointerPosition.X, PointerPosition.Y, CurrentlyTouchPressFlag);
#endif
	return PointerPosition;
}

void UMS_InputManager::HandlePinchAction(const FInputActionValue& aValue)
{
	UMS_ModeStateBase* CurrentModeState = gModeMng.GetCurrentModeState();
	if (IsValid(CurrentModeState))
	{
		CurrentModeState->OnPinchAction(aValue.Get<float>());
	}
	
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

bool UMS_InputManager::GetHitResultUnderPointerPosition(ECollisionChannel TraceChannel, bool bTraceComplex, FHitResult& HitResult) const
{
	const TObjectPtr<UWorld> World = GetWorld();
	MS_CHECK(World);

	const TObjectPtr<AMS_PlayerController> PlayerController = World->GetFirstPlayerController<AMS_PlayerController>();
	MS_CHECK(PlayerController);
	
#if PLATFORM_ANDROID_X86 || PLATFORM_ANDROID_X64 || PLATFORM_ANDROID_ARM || PLATFORM_ANDROID_ARM64 || PLATFORM_ANDROID
	return PlayerController->GetHitResultUnderFinger(ETouchIndex::Type::Touch1, TraceChannel, bTraceComplex, HitResult);
#else
	return PlayerController->GetHitResultUnderCursor(TraceChannel, bTraceComplex, HitResult);
#endif
}

bool UMS_InputManager::GetHitResultUnderPointerPosition(const FVector2D& ScreenPosition, ECollisionChannel TraceChannel, bool bTraceComplex, FHitResult& HitResult) const
{
	const TObjectPtr<UWorld> World = GetWorld();
	MS_CHECK(World);

	const TObjectPtr<AMS_PlayerController> PlayerController = World->GetFirstPlayerController<AMS_PlayerController>();
	MS_CHECK(PlayerController);

	return PlayerController->GetHitResultAtScreenPosition(ScreenPosition, TraceChannel, bTraceComplex, HitResult);
}

bool UMS_InputManager::IsPointerPressed() const
{
	return TouchInputProcessor->IsPointerPressed();
}

UMS_InputManager* UMS_InputManager::GetInstance()
{
	return InputManager;
}
