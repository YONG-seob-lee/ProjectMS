// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_Actor.h"
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
	virtual void Finalize() override;
	void DestroyAllUnits();
	
	TObjectPtr<class UMS_UnitBase> MS_CreateUnit(int32 aUnitTableId, int32 aChildTableId, const TSubclassOf<UMS_UnitBase>& aUnitType, const FVector& aPosition = FVector::ZeroVector, const FRotator& aRotator = FRotator::ZeroRotator);
	TObjectPtr<class UMS_UnitBase> MS_CreateUnit(int32 aUnitTableId, int32 aChildTableId,  EMS_UnitType aUnitType, const FVector& aPosition = FVector::ZeroVector, const FRotator& aRotator = FRotator::ZeroRotator);

	
private:
	UPROPERTY()
	TMap<uint32, TObjectPtr<UMS_UnitBase>> Units;

	uint32 LastUnitHandle = InvalidUnitHandle;

public:
	inline static TObjectPtr<UMS_UnitManager> UnitManager = nullptr;
	static UMS_UnitManager* GetInstance();

	TMap<EMS_UnitType, TSubclassOf<UMS_UnitBase>> UnitType;
#define gUnitMng (*UMS_UnitManager::GetInstance())
};
