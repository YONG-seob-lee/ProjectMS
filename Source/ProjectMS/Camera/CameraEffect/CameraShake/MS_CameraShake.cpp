#include "Camera/CameraEffect/CameraShake/MS_CameraShake.h"

UMS_CameraShake::UMS_CameraShake(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    bSingleInstance = true;

    PerlinNoiseCameraShakePattern = CreateDefaultSubobject<UPerlinNoiseCameraShakePattern>(TEXT("PerlinNoiseCameraShakePattern"));
    SetRootShakePattern(PerlinNoiseCameraShakePattern);
    PerlinNoiseCameraShakePattern->X.Amplitude = 0.0f;
    PerlinNoiseCameraShakePattern->X.Frequency = 0.0f;
    PerlinNoiseCameraShakePattern->Y.Amplitude = 1.0f;
    PerlinNoiseCameraShakePattern->Y.Frequency = 20.0f;
    PerlinNoiseCameraShakePattern->Z.Amplitude = 1.0f;
    PerlinNoiseCameraShakePattern->Z.Frequency = 20.0f;
    PerlinNoiseCameraShakePattern->BlendInTime = 0.4f;
    PerlinNoiseCameraShakePattern->BlendOutTime = 0.4f;
}
