#include "Camera/ViewCamera/MS_ViewCamera.h"

#include "Components/SceneComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "Camera/CameraEffect/CameraPostProcessEffect/MS_CameraPostProcessEffect.h"

AMS_ViewCamera::AMS_ViewCamera()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");

	SetRootComponent(SceneComponent);
	CameraComponent->SetupAttachment(SceneComponent);
}

void AMS_ViewCamera::BeginPlay()
{
	Super::BeginPlay();
}

void AMS_ViewCamera::AdjustCameraDistance(float aDistance)
{
	CameraDistance = aDistance;
	CameraComponent->SetRelativeLocationAndRotation(FVector(-CameraDistance, 0.0f, CameraDistance), FRotator(-45.0f, 0.0f, 0.0f));
}

void AMS_ViewCamera::Activate()
{
}

void AMS_ViewCamera::Deactivate()
{
}

void AMS_ViewCamera::AdjustPostProcessEffect(UMS_CameraPostProcessEffect* aCameraPostProcessEffect)
{
	if (aCameraPostProcessEffect == nullptr)
	{
		return;
	}

	CameraComponent->PostProcessSettings.AddBlendable(aCameraPostProcessEffect->PostProcessMaterial, 1.f);
}