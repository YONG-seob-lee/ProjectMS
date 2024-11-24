#include "Camera/Public/CameraEffect/MS_CameraEffect.h"

#include "Camera/Public/CameraEffect/CameraPostProcessEffect/StandardCameraPostProcessEffect/MS_StandardCameraPostProcessEffect.h"

UMS_CameraEffect::UMS_CameraEffect()
{
	CameraPostProcessEffectMap.Add(EMS_CameraPostProcessEffectType::Standard, CreateDefaultSubobject<UMS_StandardCameraPostProcessEffect>(TEXT("StandardCameraPostProcessEffect")));

	SwitchCameraPostProcessEffect(EMS_CameraPostProcessEffectType::Standard);
}

TObjectPtr<UMS_CameraPostProcessEffect> UMS_CameraEffect::GetCameraPostProcessEffect()
{
	return CameraPostProcessEffect.IsValid() ? CameraPostProcessEffect.Get() : nullptr;
}

void UMS_CameraEffect::SwitchCameraPostProcessEffect(EMS_CameraPostProcessEffectType aCameraPostProcessEffectType)
{
	UMS_CameraPostProcessEffect* TempCameraPostProcessEffect = CameraPostProcessEffectMap.Find(aCameraPostProcessEffectType)->Get();

	if (TempCameraPostProcessEffect == nullptr || CameraPostProcessEffect == TempCameraPostProcessEffect)
	{
		return;
	}

	CameraPostProcessEffect = TempCameraPostProcessEffect;
}
