#pragma once

#include "CoreMinimal.h"
#include "ProjectMS/Management/MS_ManagementBase.h"
#include "ProjectMS/Unit/MS_UnitBase.h"
#include "MS_PlayerController.generated.h"

UCLASS() class PROJECTMS_API AMS_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMS_PlayerController();
	
	virtual void PreInitializeComponents() override;
	virtual void PostInitializeComponents() override;
	
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float aDeltaTime) override;
	
	virtual void SetupInputComponent() override;

	void RegisterManagement();
	void UnRegisterManagement();

	void BindOnLevelLoadComplete();

	UFUNCTION()
	void OnLevelLoadComplete();

	void ChangeModeHelper();

	void CreateModeHelper();
	void DestroyModeHelper();

	
private:	
	
	UPROPERTY()
	TObjectPtr<UMS_UnitBase> UnitBase = nullptr;
	UPROPERTY()
	TObjectPtr<class UMS_ManagementClient> ManagementClient = nullptr;
	
	UPROPERTY()
	TObjectPtr<class UMS_LevelModeHelper> LevelModeHelper;
};