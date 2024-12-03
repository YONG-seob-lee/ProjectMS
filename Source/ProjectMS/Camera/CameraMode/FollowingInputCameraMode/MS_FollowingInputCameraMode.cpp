#include "Camera/CameraMode/FollowingInputCameraMode/MS_FollowingInputCameraMode.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"

#include "Management/MS_PlayerCameraManager.h"
#include "CoreClass/Controller/MS_PlayerController.h"

UMS_FollowingInputCameraMode::UMS_FollowingInputCameraMode()
{
}

void UMS_FollowingInputCameraMode::ActivateMode()
{
	Super::ActivateMode();

	AMS_PlayerController* PlayerController = Cast<AMS_PlayerController>(CameraManager->PCOwner);
	MS_CHECK(PlayerController);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent);
	MS_CHECK(EnhancedInputComponent);

	// TODO: UnitBase 완성시 가능

	//EnhancedInputComponent->BindAction(, ETriggerEvent::Triggered, CameraManager, TEXT("DollyIn"));
	//EnhancedInputComponent->BindAction(, ETriggerEvent::Triggered, CameraManager, TEXT("DollyOut"));
	//EnhancedInputComponent->BindAction(, ETriggerEvent::Triggered, CameraManager, TEXT("TruckLeft"));
	//EnhancedInputComponent->BindAction(, ETriggerEvent::Triggered, CameraManager, TEXT("TruckRight"));
	//EnhancedInputComponent->BindAction(, ETriggerEvent::Triggered, CameraManager, TEXT("PedestalUp"));
	//EnhancedInputComponent->BindAction(, ETriggerEvent::Triggered, CameraManager, TEXT("PedestalDown"));
	//EnhancedInputComponent->BindAction(, ETriggerEvent::Triggered, CameraManager, TEXT("RollCounterclockwise"));
	//EnhancedInputComponent->BindAction(, ETriggerEvent::Triggered, CameraManager, TEXT("RollClockwise"));
	//EnhancedInputComponent->BindAction(, ETriggerEvent::Triggered, CameraManager, TEXT("TiltUp"));
	//EnhancedInputComponent->BindAction(, ETriggerEvent::Triggered, CameraManager, TEXT("TiltDown"));
	//EnhancedInputComponent->BindAction(, ETriggerEvent::Triggered, CameraManager, TEXT("PanLeft"));
	//EnhancedInputComponent->BindAction(, ETriggerEvent::Triggered, CameraManager, TEXT("PanRight"));


#if PLATFORM_WINDOWS || PLATFORM_MAC

#elif PLATFORM_ANDROID || PLATFORM_IOS

#endif
}

void UMS_FollowingInputCameraMode::DeactivateMode()
{
	Super::DeactivateMode();

#if PLATFORM_WINDOWS || PLATFORM_MAC

#elif PLATFORM_ANDROID || PLATFORM_IOS

#endif
}
