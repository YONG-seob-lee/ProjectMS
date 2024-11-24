#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraShakeBase.h"
#include "Shakes/PerlinNoiseCameraShakePattern.h"
#include "MS_CameraShake.generated.h"

UCLASS()
class PROJECTMS_API UMS_CameraShake : public UCameraShakeBase
{
	GENERATED_BODY()

public:
	UMS_CameraShake(const FObjectInitializer& ObjectInitializer);

	// Property
public:
	UPROPERTY()
	UPerlinNoiseCameraShakePattern* PerlinNoiseCameraShakePattern = nullptr;
};
