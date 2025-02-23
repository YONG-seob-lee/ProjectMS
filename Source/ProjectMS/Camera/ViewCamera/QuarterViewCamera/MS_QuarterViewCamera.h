#pragma once

#include "CoreMinimal.h"
#include "Camera/ViewCamera/MS_ViewCamera.h"
#include "GameUserSettings/MS_GameUserSettings.h"
#include "MS_QuarterViewCamera.generated.h"

UCLASS() class PROJECTMS_API AMS_QuarterViewCamera : public AMS_ViewCamera
{
	GENERATED_BODY()

public:
	AMS_QuarterViewCamera();

	virtual void BeginPlay() override;
	
	virtual void Activate() override;
	virtual void Deactivate() override;
	
	virtual void AdjustCameraDistance(float aDistance) override;

	void SetTilt(EMS_TiltType aTiltType);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent = nullptr;
private:
	TMap<EMS_TiltType, float> Tilts; 
};
