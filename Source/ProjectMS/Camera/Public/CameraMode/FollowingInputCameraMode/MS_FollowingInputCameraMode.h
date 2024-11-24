#pragma once

#include "CoreMinimal.h"
#include "Camera/Public/CameraMode/MS_CameraMode.h"
#include "MS_FollowingInputCameraMode.generated.h"

UCLASS()
class PROJECTMS_API UMS_FollowingInputCameraMode : public UMS_CameraMode
{
	GENERATED_BODY()

public:
	UMS_FollowingInputCameraMode();

	virtual void ActivateMode() override;
	virtual void DeactivateMode() override;
};
