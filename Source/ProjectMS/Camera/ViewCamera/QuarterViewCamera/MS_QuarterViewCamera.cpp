#include "Camera/ViewCamera/QuarterViewCamera/MS_QuarterViewCamera.h"

#include "Camera/CameraComponent.h"

AMS_QuarterViewCamera::AMS_QuarterViewCamera()
{
	SceneComponent->SetAbsolute(false, true, true);

	CameraDistance = 500.0f;
	CameraComponent->SetRelativeLocationAndRotation(FVector(-CameraDistance, 0.0f, CameraDistance), FRotator(-45.0f, 0.0f, 0.0f));
}

void AMS_QuarterViewCamera::BeginPlay()
{
	Super::BeginPlay();
}

void AMS_QuarterViewCamera::AdjustCameraDistance(float aDistance)
{
    Super::AdjustCameraDistance(aDistance);

    float TargetCameraDistance = CameraDistance + (-aDistance * CAMERA_DISTANCE_STRANGTH);
    TargetCameraDistance = FMath::Clamp(TargetCameraDistance, MIN_CAMERA_DISTANCE, MAX_CAMERA_DISTANCE);

    float NewInertiaForce = (TargetCameraDistance - CameraDistance) * 0.9f;
    NewInertiaForce = FMath::Clamp(NewInertiaForce, -100.0f, 100.0f);

    if (GetWorld()->GetTimerManager().IsTimerActive(CameraInertiaTimerHandle))
    {
        CameraInertiaForce = NewInertiaForce;
        return;
    }

    CameraInertiaForce = NewInertiaForce;

    GetWorld()->GetTimerManager().SetTimer(CameraInertiaTimerHandle, [this]()
        {
            CameraInertiaForce *= 0.9f;

            if (FMath::Abs(CameraInertiaForce) < 0.01f)
            {
                CameraInertiaForce = 0.0f;
                GetWorld()->GetTimerManager().ClearTimer(CameraInertiaTimerHandle);
                return;
            }

            CameraDistance += CameraInertiaForce;
            CameraDistance = FMath::Clamp(CameraDistance, MIN_CAMERA_DISTANCE, MAX_CAMERA_DISTANCE);
            CameraComponent->SetRelativeLocationAndRotation(FVector(-CameraDistance, 0.0f, CameraDistance), FRotator(-45.0f, 0.0f, 0.0f));

        }, 0.01f, true);

}


void AMS_QuarterViewCamera::Activate()
{
	Super::Activate();
}

void AMS_QuarterViewCamera::Deactivate()
{
	Super::Deactivate();
}
