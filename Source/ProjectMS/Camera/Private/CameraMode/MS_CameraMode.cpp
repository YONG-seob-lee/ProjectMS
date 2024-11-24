#include "Camera/Public/CameraMode/MS_CameraMode.h"

#include "Management/Public/MS_PlayerCameraManager.h"

UMS_CameraMode::UMS_CameraMode()
{
}

void UMS_CameraMode::Bind(AMS_PlayerCameraManager* aCameraManager)
{
	CameraManager = aCameraManager;
}

void UMS_CameraMode::ActivateMode()
{
}

void UMS_CameraMode::DeactivateMode()
{
}
