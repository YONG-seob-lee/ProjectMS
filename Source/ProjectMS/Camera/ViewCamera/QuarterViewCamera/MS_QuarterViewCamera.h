#pragma once

#include "CoreMinimal.h"
#include "Camera/ViewCamera/MS_ViewCamera.h"
#include "MS_QuarterViewCamera.generated.h"

UCLASS()
class PROJECTMS_API AMS_QuarterViewCamera : public AMS_ViewCamera
{
	GENERATED_BODY()

public:
	AMS_QuarterViewCamera();

	virtual void BeginPlay() override;
	virtual void AdjustCameraDistance(const float& aDistance) override;
};
