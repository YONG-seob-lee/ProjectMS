// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_StaffCacheTable.h"

#include "Component/Actor/MS_AIParameterComponent.h"

void UMS_StaffCacheTable::Initialize(TObjectPtr<UMS_TableManager> aMng)
{
	Super::Initialize(aMng);

	BuildTable(aMng, EMS_TableDataType::Staff, StaffDatas);
}

void UMS_StaffCacheTable::Finalize()
{
	Super::Finalize();
}

FMS_Staff* UMS_StaffCacheTable::GetStaffData(int32 aStaffId)
{
	if(FMS_Staff** StaffData = StaffDatas.Find(aStaffId))
	{
		return *StaffData;
	}

	return nullptr;
}

void UMS_StaffCacheTable::GetStaffDatas(TMap<int32, FMS_Staff*>& aStaffDatas)
{
	aStaffDatas.Empty();
	aStaffDatas = StaffDatas;
}

void UMS_StaffCacheTable::GetStaffName(int32 aStaffId, FString& aStaffName)
{
	aStaffName = FString();
	
	FMS_Staff** Staff = StaffDatas.Find(aStaffId);
	if(!Staff)
	{
		return;
	}
	aStaffName = FText::FromStringTable(MS_LocalizedTableId::StringTable, (*Staff)->StaffNameLocalKey).ToString();
}
