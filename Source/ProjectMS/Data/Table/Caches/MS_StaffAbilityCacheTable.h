// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Table/MS_CacheTable.h"
#include "Table/RowBase/MS_StaffAbility.h"
#include "MS_StaffAbilityCacheTable.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_StaffAbilityCacheTable : public UMS_CacheTable
{
	GENERATED_BODY()
public:
	virtual void Initialize(TObjectPtr<UMS_TableManager> aMng) override;
	virtual void Finalize() override;
	
	FMS_StaffAbility* GetStaffAbilityData(int32 aStaffId);
private:
	TMap<int32, FMS_StaffAbility*> StaffAbilityDatas;
};
