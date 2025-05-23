#include "Camera/CameraMode/FollowingInputCameraMode/MS_FollowingInputCameraMode.h"

#include "EnhancedInputSubsystems.h"
#include "Manager_Client/MS_InputManager.h"
#include "Manager_Client/MS_PlayerCameraManager.h"

UMS_FollowingInputCameraMode::UMS_FollowingInputCameraMode()
{
}

void UMS_FollowingInputCameraMode::ActivateMode()
{
	Super::ActivateMode();
	
	if(const TObjectPtr CameraManager = gCameraMng)
	{
		gInputMng.OnPointerGlideDelegate.AddDynamic(CameraManager, &AMS_PlayerCameraManager::DollyAndTruck);
		gInputMng.OnPinchActionDelegate.AddDynamic(CameraManager, &AMS_PlayerCameraManager::ZoomCamera);
		gInputMng.OnMouseRightButtonGlideDelegate.AddDynamic(CameraManager, &AMS_PlayerCameraManager::DEBUG_INPUT_OrbitCamera);	
	}
}

void UMS_FollowingInputCameraMode::DeactivateMode()
{
	if(const TObjectPtr CameraManager = gCameraMng)
	{
		gInputMng.OnPointerGlideDelegate.RemoveDynamic(CameraManager, &AMS_PlayerCameraManager::DollyAndTruck);
		gInputMng.OnPinchActionDelegate.RemoveDynamic(CameraManager, &AMS_PlayerCameraManager::ZoomCamera);
		gInputMng.OnMouseRightButtonGlideDelegate.RemoveDynamic(CameraManager, &AMS_PlayerCameraManager::DEBUG_INPUT_OrbitCamera);
	}
	
	Super::DeactivateMode();
}
