#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MS_CameraMode.generated.h"

UCLASS()
class PROJECTMS_API UMS_CameraMode : public UObject
{
	GENERATED_BODY()

public:
	UMS_CameraMode();

	void Bind(class AMS_PlayerCameraManager* aCameraManager);

	UFUNCTION() virtual void ActivateMode();
	UFUNCTION() virtual void DeactivateMode();

	// Instance
public:
	TObjectPtr<class AMS_PlayerCameraManager> CameraManager = nullptr;
};
