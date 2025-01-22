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
	virtual void Finalize() override;

	
	void DestroyAllUnits();

	TObjectPtr<class UMS_UnitBase> GetUnit(MS_Handle aHandle);
	
	TObjectPtr<class UMS_UnitBase> CreateUnit(int32 aUnitTableId, int32 aChildTableId, const FVector& aPosition = FVector::ZeroVector, const FRotator& aRotator = FRotator::ZeroRotator);
	
	void DestroyUnit(MS_Handle aHandle);

protected:
	void DestroyUnit_Internal(TObjectPtr<class UMS_UnitBase> aUnitBase);

private:
	MS_Handle MakeUnitHandle(int32 aUnitTableId, int32 aChildTableId);
	
	struct FMS_ResourceUnit* GetResourceUnitData(int32 aUnitTableId) const;

	
private:
	UPROPERTY()
	TMap<uint32, TObjectPtr<UMS_UnitBase>> Units;

	uint32 LastUnitHandle = InvalidUnitHandle;

	
public:
	inline static TObjectPtr<UMS_UnitManager> UnitManager = nullptr;
	static UMS_UnitManager* GetInstance();

	TMap<EMS_UnitType, TSubclassOf<UMS_UnitBase>> UnitTypeClasses;
#define gUnitMng (*UMS_UnitManager::GetInstance())
};
