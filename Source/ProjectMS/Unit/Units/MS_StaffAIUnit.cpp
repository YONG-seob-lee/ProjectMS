// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_StaffAIUnit.h"

#include "UtilityFunctions.h"
#include "ContentsUtilities/MS_AIDefine.h"
#include "Mode/ModeObject/Container/MS_IssueTicketContainer.h"
#include "Table/RowBase/MS_Staff.h"


void UMS_StaffAIUnit::Initialize(MS_Handle aUnitHandle, EMS_UnitType aUnitType, int32 aTableId)
{
	Super::Initialize(aUnitHandle, aUnitType, aTableId);

	StaffTableData = gTableMng.GetTableRowData<FMS_Staff>(EMS_TableDataType::Staff, aTableId);
	MS_ENSURE(StaffTableData != nullptr);
}

void UMS_StaffAIUnit::Finalize()
{
	Super::Finalize();
}

void UMS_StaffAIUnit::PostInitialize()
{
	Super::PostInitialize();
}

void UMS_StaffAIUnit::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
}

int32 UMS_StaffAIUnit::GetBlueprintPathId() const
{
	return StaffTableData->PathFile;
}

UClass* UMS_StaffAIUnit::GetBlueprintClass() const
{
	int32 BPPathId = GetBlueprintPathId();
	if (BPPathId == INDEX_NONE)
	{
		return nullptr;
	}

	return UUtilityFunctions::GetClassByTablePathId(BPPathId);
}

void UMS_StaffAIUnit::RegisterPersonalAction(EMS_PersonalActionType aPersonalActionType)
{
	PersonalActions.Emplace(aPersonalActionType);
}

void UMS_StaffAIUnit::UnregisterPersonalAction(EMS_PersonalActionType aPersonalActionType)
{
	int32 RemoveNum = PersonalActions.RemoveSingle(aPersonalActionType);
}

void UMS_StaffAIUnit::OnRegistedAsIssueTicketStaff(TWeakObjectPtr<UMS_IssueTicket> aIssueTicket)
{
	IssueTicket = aIssueTicket;
}

void UMS_StaffAIUnit::OnUnregistedAsIssueTicketStaff()
{
	IssueTicket = nullptr;
}
