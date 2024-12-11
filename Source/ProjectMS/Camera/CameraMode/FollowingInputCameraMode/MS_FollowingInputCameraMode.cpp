#include "Camera/CameraMode/FollowingInputCameraMode/MS_FollowingInputCameraMode.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"

#include "Management/MS_PlayerCameraManager.h"
#include "CoreClass/Controller/MS_PlayerController.h"
#include "Camera/ViewCamera/MS_ViewCamera.h"

#include "Management/MS_TableManager.h"
#include "Data/Table/RowBase/MS_InputActionData.h"

UMS_FollowingInputCameraMode::UMS_FollowingInputCameraMode()
{
}

void UMS_FollowingInputCameraMode::ActivateMode()
{
	Super::ActivateMode();

	AMS_PlayerController* PlayerController = Cast<AMS_PlayerController>(CameraManager->PCOwner);
	MS_CHECK(PlayerController);

	PlayerController->OnPointerGlideDelegate.AddDynamic(CameraManager, &AMS_PlayerCameraManager::DollyAndTruck);
	PlayerController->OnPinchActionDelegate.AddDynamic(CameraManager->ViewCamera.Get(), &AMS_ViewCamera::AdjustCameraDistance);
}

void UMS_FollowingInputCameraMode::DeactivateMode()
{
	Super::DeactivateMode();

	AMS_PlayerController* PlayerController = Cast<AMS_PlayerController>(CameraManager->PCOwner);
	MS_CHECK(PlayerController);

	PlayerController->OnPointerGlideDelegate.RemoveDynamic(CameraManager, &AMS_PlayerCameraManager::DollyAndTruck);
	PlayerController->OnPinchActionDelegate.RemoveDynamic(CameraManager->ViewCamera.Get(), &AMS_ViewCamera::AdjustCameraDistance);
}
