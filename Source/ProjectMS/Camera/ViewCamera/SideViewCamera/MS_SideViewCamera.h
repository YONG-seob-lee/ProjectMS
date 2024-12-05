#pragma once

#include "CoreMinimal.h"
#include "Camera/ViewCamera/MS_ViewCamera.h"
#include "MS_SideViewCamera.generated.h"

UCLASS() class PROJECTMS_API AMS_SideViewCamera : public AMS_ViewCamera
{
	GENERATED_BODY()
	
public:
	AMS_SideViewCamera();

	virtual void BeginPlay() override;
	virtual void Activate() override;
	virtual void Deactivate() override;

	virtual void AdjustCameraDistance(const float& aDistance) override;
	virtual void AdjustPostProcessEffect(class UMS_CameraPostProcessEffect* aCameraPostProcessEffect) override;
};
