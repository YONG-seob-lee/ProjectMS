// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_ManagerBase.h"
#include "MS_ModeManager.generated.h"


UENUM()
enum class EMS_ModeType : uint8
{
	Normal = 0,
	Rotate = 1,		// TODO 청아 : 해당 모드는 다른 모드에서도 적용될 수 있게 해야함.
	Construct = 2,
	StaffManagement = 3,
	CustomerManagement = 4,
};

DECLARE_MULTICAST_DELEGATE_OneParam(FMS_OnSetMode, uint8);

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_ModeManager : public UMS_ManagerBase
{
	GENERATED_BODY()
public:
	UMS_ModeManager();

	void SetMode(EMS_ModeType aModeType);

	void ShowRotateWidget();
	FMS_OnSetMode OnSetMode;
	
private:
	
	
public:
	inline static TObjectPtr<UMS_ModeManager> ModeManager = nullptr;
	static UMS_ModeManager* GetInstance();
	
#define gModeMng (*UMS_ModeManager::GetInstance())
};