#include "Camera/ViewCamera/TopViewCamera/MS_TopViewCamera.h"

#include "Camera/CameraComponent.h"

AMS_TopViewCamera::AMS_TopViewCamera()
{
	SceneComponent->SetAbsolute(false, true, true);

	CameraDistance = 500.0f;
	AdjustCameraDistance(CameraDistance);
}

void AMS_TopViewCamera::BeginPlay()
{
	Super::BeginPlay();
}

void AMS_TopViewCamera::Activate()
{
	Super::Activate();

	gCameraMng.RestrictCameraMovement(true);
}

void AMS_TopViewCamera::Deactivate()
{
	Super::Deactivate();

	gCameraMng.RestrictCameraMovement(false);
}

void AMS_TopViewCamera::AdjustCameraDistance(float aDistance)
{
	Super::AdjustCameraDistance(aDistance);
	CameraComponent->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, CameraDistance), FRotator(-90.0f, 0.0f, 0.0f));
}

void AMS_TopViewCamera::AdjustPostProcessEffect(UMS_CameraPostProcessEffect* aCameraPostProcessEffect)
{
	Super::AdjustPostProcessEffect(aCameraPostProcessEffect);
}
