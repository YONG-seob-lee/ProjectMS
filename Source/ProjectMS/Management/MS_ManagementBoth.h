// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_ManagementBase.h"
#include "MS_ManagementBoth.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_ManagementBoth : public UMS_ManagementBase
{
	GENERATED_BODY()
public:
	virtual void Initialize() override;
	
private:
	UPROPERTY()
	TObjectPtr<class UMS_TableManager> TableManager = nullptr;
	
	UPROPERTY()
	TObjectPtr<class UMS_SceneManager> SceneManager = nullptr;
	
	UPROPERTY()
	TObjectPtr<class UMS_UnitManager> UnitManager = nullptr;
	
	UPROPERTY()
	TObjectPtr<class UMS_ModeManager> ModeManager = nullptr;
};
