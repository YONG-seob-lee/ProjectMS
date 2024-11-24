#include "Camera/Public/ViewCamera/QuarterViewCamera/MS_QuarterViewCamera.h"

#include "Camera/CameraComponent.h"

AMS_QuarterViewCamera::AMS_QuarterViewCamera()
{
	SceneComponent->SetAbsolute(false, true, true);

	CameraDistance = 500.0f;
	AdjustCameraDistance(CameraDistance);
}

void AMS_QuarterViewCamera::BeginPlay()
{
	Super::BeginPlay();
}

void AMS_QuarterViewCamera::AdjustCameraDistance(const float& aDistance)
{
	Super::AdjustCameraDistance(aDistance);

	CameraComponent->SetRelativeLocationAndRotation(FVector(-aDistance, 0.0f, aDistance), FRotator(-45.0f, 0.0f, 0.0f));
}
