#include "Camera/ViewCamera/SideViewCamera/MS_SideViewCamera.h"

#include "Camera/CameraComponent.h"

AMS_SideViewCamera::AMS_SideViewCamera()
{
	SceneComponent->SetAbsolute(false, true, true);

	CameraDistance = 800.0f;
	AdjustCameraDistance(CameraDistance);
}

void AMS_SideViewCamera::BeginPlay()
{
	Super::BeginPlay();
}

void AMS_SideViewCamera::AdjustCameraDistance(float aDistance)
{
	Super::AdjustCameraDistance(aDistance);
}

void AMS_SideViewCamera::AdjustPostProcessEffect(UMS_CameraPostProcessEffect* aCameraPostProcessEffect)
{
	Super::AdjustPostProcessEffect(aCameraPostProcessEffect);
}

void AMS_SideViewCamera::Activate()
{
	Super::Activate();
}

void AMS_SideViewCamera::Deactivate()
{
	Super::Deactivate();
}
