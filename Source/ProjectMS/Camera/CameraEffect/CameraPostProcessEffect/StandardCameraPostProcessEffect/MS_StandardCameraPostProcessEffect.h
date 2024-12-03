#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraEffect/CameraPostProcessEffect/MS_CameraPostProcessEffect.h"
#include "MS_StandardCameraPostProcessEffect.generated.h"

UCLASS()
class PROJECTMS_API UMS_StandardCameraPostProcessEffect : public UMS_CameraPostProcessEffect
{
	GENERATED_BODY()

public:
	UMS_StandardCameraPostProcessEffect();

	virtual void Activate() override;
	virtual void Deactivate() override;
};
