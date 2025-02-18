#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Manager_Client/MS_PlayerCameraManager.h"
#include "MS_ViewCamera.generated.h"

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float CameraDistance = 0.0f;
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Camera")
	TObjectPtr<class USceneComponent> SceneComponent = nullptr;
	
	UPROPERTY(BlueprintReadOnly, Category = "Camera")
	TObjectPtr<class UCameraComponent> CameraComponent = nullptr;
};