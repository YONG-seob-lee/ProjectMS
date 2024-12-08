// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Management/MS_ManagerBase.h"
#include "Utility/MS_Define.h"
#include "MS_UnitManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_UnitManager : public UMS_ManagerBase
{
	GENERATED_BODY()

public:
	UMS_UnitManager();
	
	TObjectPtr<class UMS_UnitBase> CreateUnit(int32 aUnitTableId, const TSubclassOf<UMS_UnitBase>& aUnitType, const FVector& aPosition = FVector::ZeroVector, const FRotator& aRotator = FRotator::ZeroRotator);

private:
	float LodScale = 1.f;
	bool bOutLineModeOn = true;

	TMap<MS_Handle, TObjectPtr<UMS_UnitBase>> Units;

public:
	inline static TObjectPtr<UMS_UnitManager> UnitManager = nullptr;
	static UMS_UnitManager* GetInstance();
	
#define gUnitMng (*UMS_UnitManager::GetInstance())
};
