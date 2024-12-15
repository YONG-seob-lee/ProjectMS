#include "Camera/CameraMode/FollowingInputCameraMode/MS_FollowingInputCameraMode.h"

#include "EnhancedInputSubsystems.h"
#include "MS_InputManager.h"
#include "Management/MS_PlayerCameraManager.h"
#include "Data/Table/RowBase/MS_InputActionData.h"

UMS_FollowingInputCameraMode::UMS_FollowingInputCameraMode()
{
}

void UMS_FollowingInputCameraMode::ActivateMode()
{
	Super::ActivateMode();

	gInputMng.OnPointerGlideDelegate.AddDynamic(CameraManager, &AMS_PlayerCameraManager::DollyAndTruck);
	gInputMng.OnPinchActionDelegate.AddDynamic(CameraManager, &AMS_PlayerCameraManager::ZoomCamera);
	gInputMng.OnMouseRightButtonGlideDelegate.AddDynamic(CameraManager, &AMS_PlayerCameraManager::DEBUGINPUT_OrbitCamera);
}

void UMS_FollowingInputCameraMode::DeactivateMode()
{
	Super::DeactivateMode();

	gInputMng.OnPointerGlideDelegate.RemoveDynamic(CameraManager, &AMS_PlayerCameraManager::DollyAndTruck);
	gInputMng.OnPinchActionDelegate.RemoveDynamic(CameraManager, &AMS_PlayerCameraManager::ZoomCamera);
	gInputMng.OnMouseRightButtonGlideDelegate.RemoveDynamic(CameraManager, &AMS_PlayerCameraManager::DEBUGINPUT_OrbitCamera);
}
