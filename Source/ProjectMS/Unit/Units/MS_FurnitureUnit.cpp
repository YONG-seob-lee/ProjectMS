// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_FurnitureUnit.h"

#include "Manager_Client/MS_ModeManager.h"
#include "Mode/ModeObject/Container/MS_IssueTicketContainer.h"
#include "Mode/ModeState/MS_ModeStateBase.h"
#include "Mode/ModeState/MS_ModeState_RunMarketBase.h"
#include "Prop/Furniture/MS_Furniture.h"
#include "Table/RowBase/MS_FurnitureData.h"


void UMS_FurnitureUnit::Initialize(MS_Handle aUnitHandle, EMS_UnitType aUnitType, int32 aTableId)
{
	Super::Initialize(aUnitHandle, aUnitType, aTableId);

	FurnitureData = gTableMng.GetTableRowData<FMS_FurnitureData>(EMS_TableDataType::Furniture, aTableId);
	MS_ENSURE(FurnitureData != nullptr);
}

void UMS_FurnitureUnit::Finalize()
{
	Super::Finalize();
}

void UMS_FurnitureUnit::PostInitialize()
{
	Super::PostInitialize();
}

void UMS_FurnitureUnit::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
}

int32 UMS_FurnitureUnit::GetBlueprintPathId() const
{
	return FurnitureData->PathFile;
}

EMS_ZoneType UMS_FurnitureUnit::GetZoneType() const
{
	return static_cast<EMS_ZoneType>(FurnitureData->ZoneType);
}

EMS_TemperatureType UMS_FurnitureUnit::GetTemperatureType() const
{
	return static_cast<EMS_TemperatureType>(FurnitureData->TemperatureType);
}

FIntVector2 UMS_FurnitureUnit::GetGridPosition() const
{
	AMS_Furniture* Furniture = GetActor<AMS_Furniture>();
	MS_ENSURE(IsValid(Furniture));

	return Furniture->GetGridPosition();
}

TArray<UMS_PropSpaceComponent*> UMS_FurnitureUnit::GetPropPurposeSpaceComponents(
	EMS_PurposeType aPropPurposeSpace) const
{
	AMS_Furniture* Furniture = GetActor<AMS_Furniture>();
	MS_ENSURE(IsValid(Furniture));

	return Furniture->GetPropPurposeSpaceComponents(aPropPurposeSpace);
}

void UMS_FurnitureUnit::UpdateIssueTickets()
{
}

void UMS_FurnitureUnit::ClearIssueTickets(bool bNeedToUpdateIssueTicketContainer)
{
	if (bNeedToUpdateIssueTicketContainer)
	{
		for (TWeakObjectPtr<UMS_IssueTicket> IssueTicket : IssueTickets)
		{
			UnregisterIssueTicket(IssueTicket);
		}
	}

	IssueTickets.Empty();
}

void UMS_FurnitureUnit::OnChangeIssueTicketRequestUnitToStaffUnit(TWeakObjectPtr<UMS_IssueTicket> aTargetTicket)
{
	if (IssueTickets.Contains(aTargetTicket))
	{
		IssueTickets.Remove(aTargetTicket);
	}
}

bool UMS_FurnitureUnit::RegisterIssueTicket(EMS_StaffIssueType aIssueType, int32 aSlotId)
{
	UMS_ModeStateBase* ModeState = gModeMng.GetCurrentModeState();
	
	if (UMS_ModeState_RunMarketBase* RunMarketMode = Cast<UMS_ModeState_RunMarketBase>(ModeState))
	{
		TWeakObjectPtr<UMS_IssueTicket> IssueTicket = RunMarketMode->RegisterIssueTicket(aIssueType, this, aSlotId);

		IssueTickets.Emplace(IssueTicket);

		return true;
	}
	
	return false;
}

bool UMS_FurnitureUnit::UnregisterIssueTicket(TWeakObjectPtr<UMS_IssueTicket> aIssueTicket)
{
	UMS_ModeStateBase* ModeState = gModeMng.GetCurrentModeState();
	
	if (UMS_ModeState_RunMarketBase* RunMarketMode = Cast<UMS_ModeState_RunMarketBase>(ModeState))
	{
		for (TWeakObjectPtr<UMS_IssueTicket> TestTicket : IssueTickets)
		{
			if (TestTicket->IsSameIssue(aIssueTicket))
			{
				IssueTickets.RemoveSingle(TestTicket);
				return RunMarketMode->UnregisterIssueTicket(aIssueTicket);
			}
		}
	}
	
	return false;
}