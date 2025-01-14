#pragma once

#include "CoreMinimal.h"
#include "Camera/ViewCamera/MS_ViewCamera.h"
#include "MS_TopViewCamera.generated.h"

UCLASS() class PROJECTMS_API AMS_TopViewCamera : public AMS_ViewCamera
{
	GENERATED_BODY()
	
public:
	AMS_TopViewCamera();

	virtual void BeginPlay() override;
	virtual void Activate() override;
	virtual void Deactivate() override;

	virtual void AdjustCameraDistance(float aDistance) override;
	virtual void AdjustPostProcessEffect(class UMS_CameraPostProcessEffect* aCameraPostProcessEffect) override;
};
