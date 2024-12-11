#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MS_ViewCamera.generated.h"

#define CAMERA_DISTANCE_STRANGTH 20.0f
#define MAX_CAMERA_DISTANCE 2000.0f
#define MIN_CAMERA_DISTANCE 300.0f

UCLASS() class PROJECTMS_API AMS_ViewCamera : public AActor
{
	GENERATED_BODY()

public:
	AMS_ViewCamera();

	virtual void BeginPlay() override;

	UFUNCTION() virtual void Activate();
	UFUNCTION() virtual void Deactivate();

	UFUNCTION() virtual void AdjustCameraDistance(float aDistance);
	UFUNCTION() virtual void AdjustPostProcessEffect(class UMS_CameraPostProcessEffect* aCameraPostProcessEffect);

	// Component
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera") TObjectPtr<class USceneComponent> SceneComponent = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera") TObjectPtr<class UCameraComponent> CameraComponent = nullptr;

	// Property
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera") float CameraDistance = 0.0f;
};