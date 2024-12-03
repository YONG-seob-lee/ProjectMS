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

void AMS_ViewCamera::AdjustCameraDistance(const float& aDistance)
{
}

void AMS_ViewCamera::AdjustPostProcessEffect(UMS_CameraPostProcessEffect* aCameraPostProcessEffect)
{
	CameraComponent->PostProcessSettings.AddBlendable(aCameraPostProcessEffect->PostProcessMaterial, 1.0f);
}
