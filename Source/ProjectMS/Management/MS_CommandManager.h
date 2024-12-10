// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_ManagerBase.h"
#include "MS_CommandManager.generated.h"

UENUM()
enum class EMS_ModeType : uint8
{
	Normal = 0,
	Rotate = 1,		// TODO 청아 : 해당 모드는 다른 모드에서도 적용될 수 있게 해야함.
	Construct = 2,
	StaffManagement = 3,
	CustomerManagement = 4,
};
/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_CommandManager : public UMS_ManagerBase
{
	GENERATED_BODY()
public:
	UMS_CommandManager();

	void SetMode(EMS_ModeType aModeType);
private:
	
	
public:
	inline static TObjectPtr<UMS_CommandManager> CommandManager = nullptr;
	static UMS_CommandManager* GetInstance();
	
#define gCommandMng (*UMS_CommandManager::GetInstance())
};
