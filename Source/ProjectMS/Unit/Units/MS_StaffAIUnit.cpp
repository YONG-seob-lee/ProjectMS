// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_StaffAIUnit.h"

#include "UtilityFunctions.h"
#include "Character/MS_CharacterBase.h"
#include "ContentsUtilities/MS_AIDefine.h"
#include "ContentsUtilities/MS_LevelDefine.h"
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

FIntVector2 UMS_StaffAIUnit::GetGridPosition() const
{
	if (GetCharacter())
	{
		FVector CharacterLocation = GetCharacter()->GetActorLocation();
		return FMS_GridData::ConvertLocationToGridPosition(CharacterLocation);
	}

	MS_ENSURE(false);
	return FIntVector2::ZeroValue;
}

EMS_StaffActionType UMS_StaffAIUnit::GetFirstStaffAction() const
{
	if (StaffActions.IsValidIndex(0))
	{
		MS_ENSURE (StaffActions[0] != EMS_StaffActionType::None);
		
		return StaffActions[0];
	}

	return EMS_StaffActionType::None;
}

void UMS_StaffAIUnit::RegisterStaffAction(EMS_StaffActionType aStaffActionType)
{
	StaffActions.Emplace(aStaffActionType);
}

void UMS_StaffAIUnit::UnregisterStaffAction(EMS_StaffActionType aStaffActionType)
{
	int32 RemoveNum = StaffActions.RemoveSingle(aStaffActionType);
}

void UMS_StaffAIUnit::OnRegisteredAsIssueTicketStaff(TWeakObjectPtr<UMS_IssueTicket> aIssueTicket)
{
	IssueTicket = aIssueTicket;
}

void UMS_StaffAIUnit::OnUnregisteredAsIssueTicketStaff()
{
	IssueTicket = nullptr;
}
