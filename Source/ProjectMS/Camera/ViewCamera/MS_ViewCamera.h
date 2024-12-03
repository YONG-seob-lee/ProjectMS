#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MS_ViewCamera.generated.h"

UCLASS()
class PROJECTMS_API AMS_ViewCamera : public AActor
{
	GENERATED_BODY()

public:
	AMS_ViewCamera();

	virtual void BeginPlay() override;

	virtual void AdjustCameraDistance(const float& aDistance);

	virtual void Activate();
	virtual void Deactivate();

	void AdjustPostProcessEffect(class UMS_CameraPostProcessEffect* aCameraPostProcessEffect);

	// Component
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera") TObjectPtr<class USceneComponent> SceneComponent = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera") TObjectPtr<class UCameraComponent> CameraComponent = nullptr;

	// Property
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float CameraDistance = 0.0f;
};