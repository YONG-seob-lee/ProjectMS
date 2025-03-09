// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_StaffAIUnit.h"

#include "MS_ConstructibleLevelScriptActorBase.h"
#include "MS_StorageUnit.h"
#include "UtilityFunctions.h"
#include "Character/MS_CharacterBase.h"
#include "Character/AICharacter/StaffAICharacter/MS_StaffAICharacter.h"
#include "ContentsUtilities/MS_AIDefine.h"
#include "Manager_Both/MS_UnitManager.h"
#include "Manager_Client/MS_ItemManager.h"
#include "Manager_Client/MS_ModeManager.h"
#include "Mode/ModeObject/Container/MS_IssueTicketContainer.h"
#include "Mode/ModeState/MS_ModeStateBase.h"
#include "Mode/ModeState/MS_ModeState_RunMarketBase.h"
#include "Prop/Spline/MS_DuckSplineActor.h"
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
	TArray<TWeakObjectPtr<UMS_UnitBase>> DuckSplineUnits; 
	gUnitMng.GetUnits(EMS_UnitType::DuckSpline, DuckSplineUnits);

	float DistanceMin = 0.f;
	TWeakObjectPtr<UMS_ActorUnitBase> NearestSplineUnit = nullptr;
	
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

	if(NearestSplineUnit == nullptr)
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
	const FVector ActorLocation = GetActorLocation();
	const FVector SplineEndPoint = DuckSplineActor->GetEndPoint();
	if(FVector::Distance(ActorLocation, SplineEndPoint) < 10.f)
	{
		return true;
	}

	return false;
}

bool UMS_StaffAIUnit::ReachSplineStartPoint() const
{
	if(DuckSplineActor.IsValid() == false)
	{
		return false;
	}
	const FVector ActorLocation = GetActorLocation();
	const FVector SplineEndPoint = DuckSplineActor->GetStartPoint();
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

void UMS_StaffAIUnit::GoingToHome() const
{
	if(DuckSplineActor.IsValid())
	{
		const FVector CurrentVehicleLocation = GetActorLocation();
		const FVector TangentLocation = -DuckSplineActor->FindTangentClosestToWorldLocation(CurrentVehicleLocation);
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

void UMS_StaffAIUnit::SetPlayerStaffData(const FMS_PlayerStaffData& aPlayerStaffData)
{
	PlayerStaffData = aPlayerStaffData;

	UpdateSkin();
}

void UMS_StaffAIUnit::UpdateSkin()
{
	AMS_StaffAICharacter* AICharacter = Cast<AMS_StaffAICharacter>(GetCharacter());
	MS_ENSURE(AICharacter);
	
	if (PlayerStaffData.PriorityOfWorks.IsValidIndex(0))
	{
		EMS_StaffIssueType PriorityIssueType = PlayerStaffData.PriorityOfWorks[0];

		if (PriorityIssueType == EMS_StaffIssueType::AddItemsToDisplay ||
			PriorityIssueType == EMS_StaffIssueType::ReturnItemsFromDisplay)
		{
			FName CapName = EquipmentName::StaffSkinB;
			FName TopName = EquipmentName::StaffSkinB;
			AICharacter->SetSkin(CapName, TopName);
		}

		else if (PriorityIssueType == EMS_StaffIssueType::AddItemsToShelf ||
			PriorityIssueType == EMS_StaffIssueType::ReturnItemsFromShelf)
		{
			FName CapName = EquipmentName::StaffSkinC;
			FName TopName = EquipmentName::StaffSkinC;
			AICharacter->SetSkin(CapName, TopName);
		}

		else
		{
			FName CapName = EquipmentName::StaffSkinA;
			FName TopName = EquipmentName::StaffSkinA;
			AICharacter->SetSkin(CapName, TopName);
		}
	}
}

void UMS_StaffAIUnit::UpdateStaffPriorityOfWorks(EMS_StaffUIPriorityType aStaffUIPriorityType)
{
	TArray<EMS_StaffIssueType> PriorityOfWorks;
	
	switch (aStaffUIPriorityType)
	{
	case EMS_StaffUIPriorityType::PaymentFirst :
		{
			PriorityOfWorks = {EMS_StaffIssueType::Payment,
				EMS_StaffIssueType::ReturnItemsFromDisplay, EMS_StaffIssueType::AddItemsToDisplay,
				EMS_StaffIssueType::ReturnItemsFromShelf, EMS_StaffIssueType::AddItemsToShelf};
			break;
		}

	case EMS_StaffUIPriorityType::DisplayFirst :
		{
			PriorityOfWorks = {EMS_StaffIssueType::ReturnItemsFromDisplay, EMS_StaffIssueType::AddItemsToDisplay,
				EMS_StaffIssueType::Payment,
				EMS_StaffIssueType::ReturnItemsFromShelf, EMS_StaffIssueType::AddItemsToShelf};
			break;
		}
		
	case EMS_StaffUIPriorityType::ShelfFirst :
		{
			PriorityOfWorks = {EMS_StaffIssueType::ReturnItemsFromShelf, EMS_StaffIssueType::AddItemsToShelf,
				EMS_StaffIssueType::Payment,
				EMS_StaffIssueType::ReturnItemsFromDisplay, EMS_StaffIssueType::AddItemsToDisplay};
			break;
		}

	case EMS_StaffUIPriorityType::PaymentOnly :
		{
			PriorityOfWorks = {EMS_StaffIssueType::Payment};
			break;
		}

	case EMS_StaffUIPriorityType::DisplayOnly :
		{
			PriorityOfWorks = {EMS_StaffIssueType::ReturnItemsFromDisplay, EMS_StaffIssueType::AddItemsToDisplay};
			break;
		}

	case EMS_StaffUIPriorityType::ShelfOnly :
		{
			PriorityOfWorks = {EMS_StaffIssueType::ReturnItemsFromShelf, EMS_StaffIssueType::AddItemsToShelf};
			break;
		}

	default:
		{
			PriorityOfWorks = {EMS_StaffIssueType::Payment,
				EMS_StaffIssueType::ReturnItemsFromDisplay, EMS_StaffIssueType::AddItemsToDisplay,
				EMS_StaffIssueType::ReturnItemsFromShelf, EMS_StaffIssueType::AddItemsToShelf};
			break;
		}
	}

	PlayerStaffData.StaffUIPriorityType = aStaffUIPriorityType;
	PlayerStaffData.PriorityOfWorks = PriorityOfWorks;
	UpdateSkin();
	
	gItemMng.UpdateStaffPriorityOfWorks(PlayerStaffData.StaffId, PlayerStaffData.StaffIdTag, PlayerStaffData.StaffUIPriorityType);
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
	NoneIssueStaffActions.RemoveSingle(aStaffActionType);
}

void UMS_StaffAIUnit::SearchAndRegisterIssueTicket()
{
	TWeakObjectPtr<UMS_IssueTicket> Ticket = SearchIssueTicket();
	if (Ticket != nullptr)
	{
		RegisterAsIssueTicketStaff(Ticket);
	}
}

TWeakObjectPtr<UMS_IssueTicket> UMS_StaffAIUnit::SearchIssueTicket() const
{
	UMS_ModeStateBase* ModeState = gModeMng.GetCurrentModeState();
	if (const UMS_ModeState_RunMarketBase* RunMarketMode = Cast<UMS_ModeState_RunMarketBase>(ModeState))
	{
		return RunMarketMode->SearchStaffIssueTicket(GetPlayerStaffData(), GetActorGridPosition());
	}

	return nullptr;
}

bool UMS_StaffAIUnit::UnregisterIssueTicket()
{
	// 자신이 이슈 티켓을 가지고 있을 경우에만 Unregister 요청 가능
	if (IssueTicket->GetRequestUnit() == this)
	{
		UMS_ModeStateBase* ModeState = gModeMng.GetCurrentModeState();
	
		if (UMS_ModeState_RunMarketBase* RunMarketMode = Cast<UMS_ModeState_RunMarketBase>(ModeState))
		{
			return RunMarketMode->UnregisterIssueTicket(IssueTicket);
		}
	}

	return false;
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
	// Slot에 아이템이 남았다면 NotPlaced로 이동
	ResetSlotDatas();
	
	// Staff 등록만 취소 후 Enable을 False 처리하고(가구에서 확인 전 다시 가져오지 못 하도록) 티켓 삭제는 가구쪽에서 담당
	if (IssueTicket == nullptr)
	{
		OnUnregisteredAsIssueTicketStaff();
	}
	else
	{
		UMS_ModeStateBase* ModeState = gModeMng.GetCurrentModeState();
		if (UMS_ModeState_RunMarketBase* RunMarketMode = Cast<UMS_ModeState_RunMarketBase>(ModeState))
		{
			RunMarketMode->UnregisterIssueTicketStaff(IssueTicket);
		}
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

TWeakObjectPtr<UMS_UnitBase> UMS_StaffAIUnit::GetIssueTicketRequestUnit()
{
	if (IssueTicket == nullptr)
	{
		UnregisterAsIssueTicketStaff();
		return nullptr;
	}
	
	return IssueTicket->GetRequestUnit();
}

bool UMS_StaffAIUnit::GetIssueTicketPickUpTargetUnits(
	TArray<TWeakObjectPtr<UMS_StorageUnit>>& aOutTargetUnits)
{
	aOutTargetUnits.Empty();

	if (IssueTicket == nullptr)
	{
		UnregisterAsIssueTicketStaff();
		return false;
	}
	
	FMS_SlotData SlotData = IssueTicket->GetRequestSlotData();
	EMS_StaffIssueType IssueType = IssueTicket->GetIssueType();

	if (IssueType != EMS_StaffIssueType::AddItemsToDisplay
	&& IssueType != EMS_StaffIssueType::AddItemsToShelf)
	{
		return false;
	}
	
	if (IssueType == EMS_StaffIssueType::AddItemsToDisplay)
	{
		TArray<TWeakObjectPtr<UMS_StorageUnit>> PickUpTargetStorages;
		if (gItemMng.CanPickUpFromStorage(SlotData.RequestItemTableId, EMS_ZoneType::Shelf, PickUpTargetStorages))
		{
			aOutTargetUnits = PickUpTargetStorages;
			return true;
		}
	}

	else if (IssueType == EMS_StaffIssueType::AddItemsToShelf)
	{
		TArray<TWeakObjectPtr<UMS_StorageUnit>> PickUpTargetStorages;
		if (gItemMng.CanPickUpFromStorage(SlotData.RequestItemTableId, EMS_ZoneType::Pallet, PickUpTargetStorages))
		{
			aOutTargetUnits = PickUpTargetStorages;
			return true;
		}
	}

	return false;
}

bool UMS_StaffAIUnit::GetIssueTicketDeliveryTargetUnits(TArray<TWeakObjectPtr<UMS_StorageUnit>>& aOutTargetUnits)
{
	aOutTargetUnits.Empty();

	if (IssueTicket == nullptr)
	{
		UnregisterAsIssueTicketStaff();
		return false;
	}
	
	FMS_SlotData SlotData = IssueTicket->GetRequestSlotData();
	EMS_StaffIssueType IssueType = IssueTicket->GetIssueType();

	if (IssueType != EMS_StaffIssueType::ReturnItemsFromDisplay
	&& IssueType != EMS_StaffIssueType::ReturnItemsFromShelf)
	{
		return false;
	}
	
	if (IssueType == EMS_StaffIssueType::ReturnItemsFromDisplay)
	{
		TArray<TWeakObjectPtr<UMS_StorageUnit>> DeliveryTargetStorages;
		if (gItemMng.CanDeliveryToStorage(SlotData.CurrentItemTableId, SlotData.CurrentItemCount, EMS_ZoneType::Shelf, DeliveryTargetStorages))
		{
			aOutTargetUnits = DeliveryTargetStorages;
			return true;
		}
	}

	else if (IssueType == EMS_StaffIssueType::ReturnItemsFromShelf)
	{
		TArray<TWeakObjectPtr<UMS_StorageUnit>> DeliveryTargetStorages;
		if (gItemMng.CanDeliveryToStorage(SlotData.CurrentItemTableId, SlotData.CurrentItemCount, EMS_ZoneType::Pallet, DeliveryTargetStorages))
		{
			aOutTargetUnits = DeliveryTargetStorages;
			return true;
		}
	}

	return false;
}

bool UMS_StaffAIUnit::DeliveryItems()
{
	/*if (IssueTicket == nullptr)
	{
		UnregisterAsIssueTicketStaff();
		return false;
	}
	
	EMS_StaffIssueType IssueType = IssueTicket->GetIssueType();
	
	if (IssueType != EMS_StaffIssueType::ReturnItemsFromDisplay
	&& IssueType != EMS_StaffIssueType::ReturnItemsFromShelf
	&& IssueType != EMS_StaffIssueType::AddItemsToDisplay
	&& IssueType != EMS_StaffIssueType::AddItemsToShelf)
	{
		MS_ENSURE(false);
		return false;
	}*/
	
	if (!SlotDatas.IsValidIndex(0) || SlotDatas[0].CurrentItemTableId == INDEX_NONE || SlotDatas[0].CurrentItemCount == 0)	// 직원이 아이템을 들고 있는지
	{
		MS_ENSURE(false);
		return false;
	}
	
	// Delivery
	TWeakObjectPtr<UMS_FurnitureUnit> FurnitureUnit = GetInteractableFurnitureUnit();
	if (UMS_StorageUnit* StorageUnit = Cast<UMS_StorageUnit>(FurnitureUnit))
	{
		//if (IssueType == EMS_StaffIssueType::ReturnItemsFromDisplay
		//|| IssueType == EMS_StaffIssueType::ReturnItemsFromShelf)
		//{
		int32 MoveCount = StorageUnit->AddAnySlotCurrentItemCount(SlotDatas[0].CurrentItemTableId, SlotDatas[0].CurrentItemCount);
		if (MoveCount == 0)
		{
			return false;
		}
		
		SubtractCurrentItemCount(0, SlotDatas[0].CurrentItemTableId, MoveCount);
		return true;
		//}

		/*
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
				int32 MoveCount = FMath::Min(SlotMaxCount - RequestSlotData.CurrentItemCount, SlotDatas[0].CurrentItemCount);
			
				if (StorageUnit->AddCurrentItemCount(IssueTicket->GetRequestSlotId(), RequestSlotData.RequestItemTableId, MoveCount))
				{
					SubtractCurrentItemCount(0, RequestSlotData.RequestItemTableId, MoveCount);
				}
			}
		}
		*/
	}

	return false;
}

bool UMS_StaffAIUnit::PickUpRequestItems()	// Add할 아이템 꺼내기
{
	if (IssueTicket == nullptr)
	{
		UnregisterAsIssueTicketStaff();
		return false;
	}
	
	EMS_StaffIssueType IssueType = IssueTicket->GetIssueType();
	
	if (IssueType != EMS_StaffIssueType::AddItemsToDisplay
	&& IssueType != EMS_StaffIssueType::AddItemsToShelf)
	{
		MS_ENSURE(false);
		return false;
	}
	
	FMS_SlotData RequestSlotData = IssueTicket->GetRequestSlotData();

	if (RequestSlotData.RequestItemTableId != RequestSlotData.CurrentItemTableId)
	{
		if (RequestSlotData.CurrentItemCount != 0)	// Request Item과 CurrentItem이 다르면 아이템이 없어야 Add 가능
		{
			MS_ENSURE(false);
			return false;
		}
	}
	
	if (!SlotDatas.IsValidIndex(0) || SlotDatas[0].CurrentItemCount != 0)	// 직원 슬롯에 공간이 남았는지
	{
		MS_ENSURE(false);
		return false;
	}

	FMS_ItemData* RequestItemData = gTableMng.GetTableRowData<FMS_ItemData>(EMS_TableDataType::ItemData, RequestSlotData.RequestItemTableId);
	if (RequestItemData == nullptr)
	{
		MS_ENSURE(false);
		return false;
	}

	// Request Count
	int32 SlotMaxCount = IssueType == EMS_StaffIssueType::AddItemsToDisplay ? RequestItemData->Slot100x100MaxCount : RequestItemData->BoxMaxCount;
	int32 RequestCount = SlotMaxCount - RequestSlotData.CurrentItemCount;

	// Pick Up
	TWeakObjectPtr<UMS_FurnitureUnit> FurnitureUnit = GetInteractableFurnitureUnit();
	if (UMS_StorageUnit* StorageUnit = Cast<UMS_StorageUnit>(FurnitureUnit))
	{
		int32 MoveCount = StorageUnit->SubtractAnySlotCurrentItemCount(RequestSlotData.RequestItemTableId, RequestCount);
		if (MoveCount == 0)
		{
			return false;
		}

		AddCurrentItemCount(0, RequestSlotData.RequestItemTableId, MoveCount);

		if (StorageUnit->GetZoneType() == EMS_ZoneType::Pallet)
		{
			gItemMng.UpdateNotPlacedItemsToPalletItems(StorageUnit);
		}
		
		return true;
	}
	
	return false;
}

bool UMS_StaffAIUnit::PickUpCurrentItems()	// Reture하기 위해 아이템 빼기
{
	if (IssueTicket == nullptr)
	{
		UnregisterAsIssueTicketStaff();
		return false;
	}
	
	EMS_StaffIssueType IssueType = IssueTicket->GetIssueType();
	
	if (IssueType != EMS_StaffIssueType::ReturnItemsFromDisplay
	&& IssueType != EMS_StaffIssueType::ReturnItemsFromShelf)
	{
		MS_ENSURE(false);
		return false;
	}
	
	FMS_SlotData RequestSlotData = IssueTicket->GetRequestSlotData();

	if (RequestSlotData.RequestItemTableId == RequestSlotData.CurrentItemTableId)	// 뺄 필요가 없음
	{
		MS_ENSURE(false);
		return false;
	}

	if (!SlotDatas.IsValidIndex(0) || SlotDatas[0].CurrentItemCount != 0)	// 직원 슬롯에 공간이 남았는지
	{
		MS_ENSURE(false);
		return false;
	}

	TWeakObjectPtr<UMS_FurnitureUnit> FurnitureUnit = GetInteractableFurnitureUnit();
	if (UMS_StorageUnit* StorageUnit = Cast<UMS_StorageUnit>(FurnitureUnit))
	{
		// 가구 유닛에서 아이템을 빼면서 가구 유닛이 이슈랑 상관없어지면 스태프에게 일임하여 이슈가 사라지는 것을 방지
		IssueTicket->ChangeRequestUnitToStaffUnit();

		// 아이템 옮기기
		int32 MoveCount = StorageUnit->SubtractAnySlotCurrentItemCount(RequestSlotData.CurrentItemTableId, RequestSlotData.CurrentItemCount);
		if (MoveCount == 0)
		{
			return false;
		}

		AddCurrentItemCount(0, RequestSlotData.CurrentItemTableId, MoveCount);

		if (StorageUnit->GetZoneType() == EMS_ZoneType::Pallet)
		{
			gItemMng.UpdateNotPlacedItemsToPalletItems(StorageUnit);
		}
		
		return true;
	}
	
	return false;
}

void UMS_StaffAIUnit::OnChangeCurrentSlotDatas()
{
	Super::OnChangeCurrentSlotDatas();

	if (IssueTicket != nullptr)
	{
		if (IssueTicket->GetRequestUnit() == this)
		{
			if (SlotDatas.IsValidIndex(0))
			{
				if (SlotDatas[0].CurrentItemCount == 0)
				{
					UnregisterIssueTicket();
				}
			}
		}
	}
}
