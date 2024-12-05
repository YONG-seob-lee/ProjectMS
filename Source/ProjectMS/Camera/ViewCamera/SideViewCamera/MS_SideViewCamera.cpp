#include "Camera/ViewCamera/SideViewCamera/MS_SideViewCamera.h"

#include "Camera/CameraComponent.h"

AMS_SideViewCamera::AMS_SideViewCamera()
{
	SceneComponent->SetAbsolute(false, true, true);

	CameraDistance = 800.0f;
	AdjustCameraDistance(CameraDistance);

	SetActorRotation(FRotator(0.0f, -90.0f, 0.0f));
}

void AMS_SideViewCamera::BeginPlay()
{
	Super::BeginPlay();
}

void AMS_SideViewCamera::AdjustCameraDistance(const float& aDistance)
{
	Super::AdjustCameraDistance(aDistance);

	CameraComponent->SetRelativeLocationAndRotation(FVector(-aDistance, 0.0f, aDistance / 10.0f), FRotator(0.0f, 0.0f, 0.0f));
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
