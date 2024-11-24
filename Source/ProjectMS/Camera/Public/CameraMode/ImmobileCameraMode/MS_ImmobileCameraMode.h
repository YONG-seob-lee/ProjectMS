#pragma once

#include "CoreMinimal.h"
#include "Camera/Public/CameraMode/MS_CameraMode.h"
#include "MS_ImmobileCameraMode.generated.h"

UCLASS()
class PROJECTMS_API UMS_ImmobileCameraMode : public UMS_CameraMode
{
	GENERATED_BODY()

public:
	UMS_ImmobileCameraMode();

	virtual void ActivateMode() override;
	virtual void DeactivateMode() override;
};
