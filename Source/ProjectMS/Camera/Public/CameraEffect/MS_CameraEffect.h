#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MS_CameraEffect.generated.h"

UENUM()
enum class EMS_CameraPostProcessEffectType
{
	Undefined,
	Standard
};

UCLASS()
class PROJECTMS_API UMS_CameraEffect : public UObject
{
	GENERATED_BODY()

public:
	UMS_CameraEffect();

	FORCEINLINE
		TObjectPtr<class UMS_CameraPostProcessEffect> GetCameraPostProcessEffect();
	UFUNCTION(BlueprintCallable)
	void SwitchCameraPostProcessEffect(EMS_CameraPostProcessEffectType aCameraPostProcessEffectType);

	// Instance
private:
	TMap<EMS_CameraPostProcessEffectType, TObjectPtr<class UMS_CameraPostProcessEffect>> CameraPostProcessEffectMap = {};
	TWeakObjectPtr<class UMS_CameraPostProcessEffect> CameraPostProcessEffect = nullptr;
};
