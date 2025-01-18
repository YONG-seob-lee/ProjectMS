// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_StaffAbilityCacheTable.h"

void UMS_StaffAbilityCacheTable::Initialize(TObjectPtr<UMS_TableManager> aMng)
{
	Super::Initialize(aMng);

	BuildTable(aMng, EMS_TableDataType::Staff, StaffAbilityDatas);
}

void UMS_StaffAbilityCacheTable::Finalize()
{
	Super::Finalize();
}

FMS_StaffAbility* UMS_StaffAbilityCacheTable::GetStaffAbilityData(int32 aStaffId)
{
	for(const auto& StaffAbilityData : StaffAbilityDatas)
	{
		if(StaffAbilityData.Value->StaffId == aStaffId)
		{
			return StaffAbilityData.Value;
		}
	}

	return nullptr;
}