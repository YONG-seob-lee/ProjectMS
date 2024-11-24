#pragma once

#include "CoreMinimal.h"
#include "Camera/Public/CameraMode/MS_CameraMode.h"
#include "MS_FollowingPlayerCameraMode.generated.h"

UCLASS()
class PROJECTMS_API UMS_FollowingPlayerCameraMode : public UMS_CameraMode
{
	GENERATED_BODY()

public:
	UMS_FollowingPlayerCameraMode();

	virtual void ActivateMode() override;
	virtual void DeactivateMode() override;

};
