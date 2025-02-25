// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_StaffAIUnit.h"

#include "MS_ConstructibleLevelScriptActorBase.h"
#include "MS_FurnitureUnit.h"
#include "UtilityFunctions.h"
#include "Character/MS_CharacterBase.h"
#include "Character/AICharacter/OutsideAICharacter/MS_DuckSplineActor.h"
#include "ContentsUtilities/MS_AIDefine.h"
#include "Manager_Both/MS_UnitManager.h"
#include "Manager_Client/MS_ItemManager.h"
#include "Manager_Client/MS_ModeManager.h"
#include "Manager_Client/MS_SceneManager.h"
#include "Mode/ModeObject/Container/MS_IssueTicketContainer.h"
#include "Mode/ModeState/MS_ModeStateBase.h"
#include "Mode/ModeState/MS_ModeState_RunMarketBase.h"
#include "Prop/Furniture/MS_Furniture.h"
#include "Table/RowBase/MS_ItemData.h"
#include "Table/RowBase/MS_Staff.h"


void UMS_StaffAIUnit::Initialize(MS_Handle aUnitHandle, EMS_UnitType aUnitType, int32 aTableId)
{
	Super::Initialize(aUnitHandle, aUnitType, aTableId);

	StaffTableData = gTableMng.GetTableRowData<FMS_Staff>(EMS_TableDataType::Staff, aTableId);
	MS_ENSURE(StaffTableData != nullptr);

	int32 SlotCount = StaffTableData->SlotCount;
	for (int32 i = 0; i < SlotCount; ++i)
	{
		SlotDatas.Emplace(FMS_SlotData());
	}
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

void UMS_StaffAIUnit::DestroyUnitActor()
{
	// ToDo: 근본적인 문제 해결 필요
	/* GetWorld()->DestroyActor(Character)를 실행하면 게임 강제 종료 시 FidRef() 함수에서 크래시 발생
	 * 아래와 같이 처리 시 레벨 이동할 때 정상적으로 삭제되는 점은 확인했다.
	 */
	if (StaffTableData->PreSpawned == false)
	{
		Super::DestroyUnitActor();
	}
	else
	{
		if(IsValid(Character))
		{
			Character->Destroy();
			Character->SetHidden(true);
			// GetWorld()->DestroyActor(Character);
			Character = nullptr;
		}
	}
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

bool UMS_StaffAIUnit::FindNearestSpline()
{
	TArray<TObjectPtr<UMS_UnitBase>> DuckSplineUnits; 
	gUnitMng.GetUnits(EMS_UnitType::DuckSpline, DuckSplineUnits);

	float DistanceMin = 0.f;
	TObjectPtr<UMS_ActorUnitBase> NearestSplineUnit = nullptr;
	
	for(const auto& SplineUnit : DuckSplineUnits)
	{
		if(const TObjectPtr<UMS_ActorUnitBase> SplineActorUnit = Cast<UMS_ActorUnitBase>(SplineUnit))
		{
			const float Distance = FVector::Distance(GetActorLocation(), SplineActorUnit->GetUnitPosition());
			if(DistanceMin == 0.f || DistanceMin > Distance)
			{
				DistanceMin = Distance;
				NearestSplineUnit = SplineActorUnit;
			}
		}
	}

	if(!NearestSplineUnit)
	{
		return false;
	}

	if(const TObjectPtr<AMS_DuckSplineActor> SplineActor = Cast<AMS_DuckSplineActor>(NearestSplineUnit->GetActor()))
	{
		DuckSplineActor = SplineActor;
		return true;
	}

	return false;
}

bool UMS_StaffAIUnit::ReachSplineEndPoint() const
{
	if(DuckSplineActor.IsValid() == false)
	{
		return false;
	}
	FVector ActorLocation = GetActorLocation();
	FVector SplineEndPoint = DuckSplineActor->GetEndPoint();
	if(FVector::Distance(ActorLocation, SplineEndPoint) < 10.f)
	{
		return true;
	}

	return false;
}

void UMS_StaffAIUnit::GoingToWork() const
{
	if(DuckSplineActor.IsValid())
	{
		const FVector CurrentVehicleLocation = GetActorLocation();
		const FVector TangentLocation = DuckSplineActor->FindTangentClosestToWorldLocation(CurrentVehicleLocation);
		FRotator MoveNextRotation = TangentLocation.Rotation();
		MoveNextRotation.Yaw -= 90.f;
		const FVector ClosetLocation = DuckSplineActor->FindLocationClosestToWorldLocation(CurrentVehicleLocation);
		if(const TObjectPtr<AMS_CharacterBase> StaffCharacter = GetCharacter())
		{
			StaffCharacter->SetActorLocation(ClosetLocation + TangentLocation.GetSafeNormal() * 5.f);
			StaffCharacter->SetActorRotation(MoveNextRotation);
		}
	}
}

bool UMS_StaffAIUnit::HasStaffAction() const
{
	if (!NoneIssueStaffActions.IsEmpty())
	{
		return true;
	}

	if (IssueTicket != nullptr)
	{
		return true;
	}

	return false;
}

EMS_StaffActionType UMS_StaffAIUnit::GetFirstStaffAction(TWeakObjectPtr<UMS_IssueTicket>& OutIssueTicket)
{
	if (NoneIssueStaffActions.IsValidIndex(0))
	{
		MS_ENSURE (NoneIssueStaffActions[0] != EMS_StaffActionType::None);

		OutIssueTicket = nullptr;
		return NoneIssueStaffActions[0];
	}

	if (IssueTicket != nullptr)
	{
		OutIssueTicket = IssueTicket;
		return EMS_StaffActionType::Issue;
	}

	if(bGotoWork == false)
	{
		return EMS_StaffActionType::GoingHome;
	}

	else
	{
		SearchAndRegisterIssueTicket();
		if (IssueTicket != nullptr)
		{
			OutIssueTicket = IssueTicket;
			return EMS_StaffActionType::Issue;
		}

		OutIssueTicket = nullptr;
		return EMS_StaffActionType::None;
	}
}

void UMS_StaffAIUnit::RegisterNoneIssueStaffAction(EMS_StaffActionType aStaffActionType)
{
	NoneIssueStaffActions.Emplace(aStaffActionType);
}

void UMS_StaffAIUnit::UnregisterNoneIssueStaffAction(EMS_StaffActionType aStaffActionType)
{
	int32 RemoveNum = NoneIssueStaffActions.RemoveSingle(aStaffActionType);
}

void UMS_StaffAIUnit::SearchAndRegisterIssueTicket()
{
	TWeakObjectPtr<class UMS_IssueTicket> Ticket = SearchIssueTicket();
	if (Ticket != nullptr)
	{
		RegisterAsIssueTicketStaff(Ticket);
	}
}

TWeakObjectPtr<class UMS_IssueTicket> UMS_StaffAIUnit::SearchIssueTicket() const
{
	UMS_ModeStateBase* ModeState = gModeMng.GetCurrentModeState();
	if (const UMS_ModeState_RunMarketBase* RunMarketMode = Cast<UMS_ModeState_RunMarketBase>(ModeState))
	{
		return RunMarketMode->SearchStaffIssueTicket(GetPlayerStaffData(), GetActorGridPosition());
	}

	return nullptr;
}

void UMS_StaffAIUnit::RegisterAsIssueTicketStaff(TWeakObjectPtr<UMS_IssueTicket>& aTargetTicket)
{
	UMS_ModeStateBase* ModeState = gModeMng.GetCurrentModeState();
	if (UMS_ModeState_RunMarketBase* RunMarketMode = Cast<UMS_ModeState_RunMarketBase>(ModeState))
	{
		RunMarketMode->RegisterIssueTicketStaff(aTargetTicket, this);
	}
}

void UMS_StaffAIUnit::UnregisterAsIssueTicketStaff()
{
	UMS_ModeStateBase* ModeState = gModeMng.GetCurrentModeState();
	if (UMS_ModeState_RunMarketBase* RunMarketMode = Cast<UMS_ModeState_RunMarketBase>(ModeState))
	{
		RunMarketMode->UnregisterIssueTicketStaff(IssueTicket);
	}
}

void UMS_StaffAIUnit::OnRegisteredAsIssueTicketStaff(TWeakObjectPtr<UMS_IssueTicket> aIssueTicket)
{
	IssueTicket = aIssueTicket;
}

void UMS_StaffAIUnit::OnUnregisteredAsIssueTicketStaff()
{
	IssueTicket = nullptr;
}

TWeakObjectPtr<class UMS_FurnitureUnit> UMS_StaffAIUnit::GetIssueTicketRequestFurnitrueUnit() const
{
	if (IssueTicket != nullptr)
	{
		return IssueTicket->GetRequestFurnitureUnit();
	}

	return nullptr;
}

bool UMS_StaffAIUnit::GetIssueTicketTakeOutTargetUnits(
	TArray<TWeakObjectPtr<UMS_FurnitureUnit>>& aOutTargetUnits) const
{
	aOutTargetUnits.Empty();

	FMS_SlotData SlotData = IssueTicket->GetRequestSlotData();
	EMS_StaffIssueType IssueType = IssueTicket->GetIssueType();

	if (IssueType != EMS_StaffIssueType::AddItemsToDisplay
	&& IssueType != EMS_StaffIssueType::AddItemsToShelf)
	{
		return false;
	}
	
	if (IssueType == EMS_StaffIssueType::AddItemsToDisplay)
	{
		TArray<TWeakObjectPtr<class UMS_FurnitureUnit>> TakeOutTargetFurnitrues;
		if (gItemMng.CanTakeOutFromStorage(SlotData.RequestItemTableId, EMS_ZoneType::Shelf, TakeOutTargetFurnitrues))
		{
			aOutTargetUnits = TakeOutTargetFurnitrues;
			return true;
		}
	}

	else if (IssueType == EMS_StaffIssueType::AddItemsToShelf)
	{
		TArray<TWeakObjectPtr<class UMS_FurnitureUnit>> TakeOutTargetFurnitrues;
		if (gItemMng.CanTakeOutFromStorage(SlotData.RequestItemTableId, EMS_ZoneType::Pallet, TakeOutTargetFurnitrues))
		{
			aOutTargetUnits = TakeOutTargetFurnitrues;
			return true;
		}
	}

	return false;
}

bool UMS_StaffAIUnit::GetIssueTicketTakeInTargetUnits(TArray<TWeakObjectPtr<UMS_FurnitureUnit>>& aOutTargetUnits) const
{
	aOutTargetUnits.Empty();

	FMS_SlotData SlotData = IssueTicket->GetRequestSlotData();
	EMS_StaffIssueType IssueType = IssueTicket->GetIssueType();

	if (IssueType != EMS_StaffIssueType::ReturnItemsFromDisplay
	&& IssueType != EMS_StaffIssueType::ReturnItemsFromShelf)
	{
		return false;
	}
	
	if (IssueType == EMS_StaffIssueType::ReturnItemsFromDisplay)
	{
		TArray<TWeakObjectPtr<class UMS_FurnitureUnit>> TakeInTargetFurnitrues;
		if (gItemMng.CanTakeInToStorage(SlotData.CurrentItemTableId, SlotData.CurrentItemCount, EMS_ZoneType::Shelf, TakeInTargetFurnitrues))
		{
			aOutTargetUnits = TakeInTargetFurnitrues;
			return true;
		}
	}

	else if (IssueType == EMS_StaffIssueType::ReturnItemsFromShelf)
	{
		TArray<TWeakObjectPtr<class UMS_FurnitureUnit>> TakeInTargetFurnitrues;
		if (gItemMng.CanTakeInToStorage(SlotData.CurrentItemTableId, SlotData.CurrentItemCount, EMS_ZoneType::Pallet, TakeInTargetFurnitrues))
		{
			aOutTargetUnits = TakeInTargetFurnitrues;
			return true;
		}
	}

	return false;
}

void UMS_StaffAIUnit::TakeInItems()
{
	EMS_StaffIssueType IssueType = IssueTicket->GetIssueType();
	
	if (IssueType != EMS_StaffIssueType::ReturnItemsFromDisplay
	&& IssueType != EMS_StaffIssueType::ReturnItemsFromShelf
	&& IssueType != EMS_StaffIssueType::AddItemsToDisplay
	&& IssueType != EMS_StaffIssueType::AddItemsToShelf)
	{
		MS_ENSURE(false);
		return;
	}
	
	if (!SlotDatas.IsValidIndex(0) || SlotDatas[0].CurrentItemTableId == INDEX_NONE || SlotDatas[0].CurrentItemCount == 0)	// 직원이 아이템을 들고 있는지
	{
		MS_ENSURE(false);
		return;
	}
	
	// Take In
	TWeakObjectPtr<UMS_FurnitureUnit> FurnitureUnit = GetInteractableFurnitureUnit();
	if (FurnitureUnit == nullptr)
	{
		MS_ENSURE(false);
		return;
	}

	if (IssueType == EMS_StaffIssueType::ReturnItemsFromDisplay
		|| IssueType == EMS_StaffIssueType::ReturnItemsFromShelf)
	{
		int32 MoveCount = FurnitureUnit->AddAnySlotCurrentItemCount(SlotDatas[0].CurrentItemTableId, SlotDatas[0].CurrentItemCount);
		SubtractCurrentItemCount(0, SlotDatas[0].CurrentItemTableId, MoveCount);
	}

	else
	{
		FMS_SlotData RequestSlotData = IssueTicket->GetRequestSlotData();
		
		if (RequestSlotData.RequestItemTableId == SlotDatas[0].CurrentItemTableId)
		{
			FMS_ItemData* RequestItemData = gTableMng.GetTableRowData<FMS_ItemData>(EMS_TableDataType::ItemData, RequestSlotData.RequestItemTableId);
			if (RequestItemData == nullptr)
			{
				MS_ENSURE(false);
				return;
			}
			
			int32 SlotMaxCount = IssueType == EMS_StaffIssueType::AddItemsToDisplay ? RequestItemData->Slot100x100MaxCount : RequestItemData->BoxMaxCount;
			int32 TakeInCount = FMath::Min(SlotMaxCount - RequestSlotData.CurrentItemCount, SlotDatas[0].CurrentItemCount);
			
			if (FurnitureUnit->AddCurrentItemCount(IssueTicket->GetRequestSlotId(), RequestSlotData.RequestItemTableId, TakeInCount))
			{
				SubtractCurrentItemCount(0, RequestSlotData.RequestItemTableId, TakeInCount);
			}
		}
	}
}

void UMS_StaffAIUnit::TakeOutRequestItems()	// Add할 아이템 꺼내기
{
	EMS_StaffIssueType IssueType = IssueTicket->GetIssueType();
	
	if (IssueType != EMS_StaffIssueType::AddItemsToDisplay
	&& IssueType != EMS_StaffIssueType::AddItemsToShelf)
	{
		MS_ENSURE(false);
		return;
	}
	
	FMS_SlotData RequestSlotData = IssueTicket->GetRequestSlotData();

	if (RequestSlotData.RequestItemTableId != RequestSlotData.CurrentItemTableId)
	{
		if (RequestSlotData.CurrentItemCount != 0)	// Request Item과 CurrentItem이 다르면 아이템이 없어야 Add 가능
		{
			MS_ENSURE(false);
			return;
		}
	}
	
	if (!SlotDatas.IsValidIndex(0) || SlotDatas[0].CurrentItemCount != 0)	// 직원 슬롯에 공간이 남았는지
	{
		MS_ENSURE(false);
		return;
	}

	FMS_ItemData* RequestItemData = gTableMng.GetTableRowData<FMS_ItemData>(EMS_TableDataType::ItemData, RequestSlotData.RequestItemTableId);
	if (RequestItemData == nullptr)
	{
		MS_ENSURE(false);
		return;
	}

	// Request Count
	int32 SlotMaxCount = IssueType == EMS_StaffIssueType::AddItemsToDisplay ? RequestItemData->Slot100x100MaxCount : RequestItemData->BoxMaxCount;
	int32 RequestCount = SlotMaxCount - RequestSlotData.CurrentItemCount;

	// Take Out
	TWeakObjectPtr<UMS_FurnitureUnit> FurnitureUnit = GetInteractableFurnitureUnit();
	if (FurnitureUnit == nullptr)
	{
		MS_ENSURE(false);
		return;
	}

	int32 MoveCount = FurnitureUnit->SubtractAnySlotCurrentItemCount(RequestSlotData.RequestItemTableId, RequestCount);
	AddCurrentItemCount(0, RequestSlotData.RequestItemTableId, MoveCount);
}

void UMS_StaffAIUnit::TakeOutCurrentItems()	// Reture하기 위해 아이템 빼기
{
	EMS_StaffIssueType IssueType = IssueTicket->GetIssueType();
	
	if (IssueType != EMS_StaffIssueType::ReturnItemsFromDisplay
	&& IssueType != EMS_StaffIssueType::ReturnItemsFromShelf)
	{
		MS_ENSURE(false);
		return;
	}
	
	FMS_SlotData RequestSlotData = IssueTicket->GetRequestSlotData();

	if (RequestSlotData.RequestItemTableId == RequestSlotData.CurrentItemTableId)	// 뺄 필요가 없음
	{
		MS_ENSURE(false);
		return;
	}

	if (!SlotDatas.IsValidIndex(0) || SlotDatas[0].CurrentItemCount != 0)	// 직원 슬롯에 공간이 남았는지
	{
		MS_ENSURE(false);
		return;
	}

	TWeakObjectPtr<UMS_FurnitureUnit> FurnitureUnit = GetInteractableFurnitureUnit();
	if (FurnitureUnit == nullptr)
	{
		MS_ENSURE(false);
		return;
	}

	int32 MoveCount = FurnitureUnit->SubtractAnySlotCurrentItemCount(RequestSlotData.CurrentItemTableId, RequestSlotData.CurrentItemCount);
	AddCurrentItemCount(0, RequestSlotData.CurrentItemTableId, MoveCount);
}

TWeakObjectPtr<UMS_FurnitureUnit> UMS_StaffAIUnit::GetInteractableFurnitureUnit()
{
	if (AMS_ConstructibleLevelScriptActorBase* LevelScriptActor = Cast<AMS_ConstructibleLevelScriptActorBase>(gSceneMng.GetCurrentLevelScriptActor()))
	{
		TWeakObjectPtr<AActor> Actor = LevelScriptActor->GetGridObject(GetActorGridPosition());

		if (Actor != nullptr)
		{
			if (AMS_Furniture* FurnitureActor = Cast<AMS_Furniture>(Actor.Get()))
			{
				return Cast<UMS_FurnitureUnit>(FurnitureActor->GetOwnerUnitBase());
			}
		}
	}
	
	return nullptr;
}
