#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MS_CameraPostProcessEffect.generated.h"

UCLASS()
class PROJECTMS_API UMS_CameraPostProcessEffect : public UObject
{
	GENERATED_BODY()

public:
	UMS_CameraPostProcessEffect();

	virtual void Activate();
	virtual void Deactivate();

	// Property
public:
	FPostProcessSettings PostProcessSettings = {};

	// Instance
public:
	TObjectPtr<UMaterial> PostProcessMaterial = nullptr;
};
