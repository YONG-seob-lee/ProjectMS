// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_SlotChildActorComponent.h"

#include "MS_Define.h"
#include "UtilityFunctions.h"
#include "Item/MS_SlotActor.h"
#include "Manager_Both/MS_TableManager.h"
#include "Table/RowBase/MS_ItemData.h"


UMS_SlotChildActorComponent::UMS_SlotChildActorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UMS_SlotChildActorComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UMS_SlotChildActorComponent::OnChangeRequestSlotData(const FMS_SlotData& aSlotDatas)
{
	if (CacheSlotData.RequestItemTableId == aSlotDatas.RequestItemTableId)
	{
		return;
	}

	CacheSlotData = aSlotDatas;
}

void UMS_SlotChildActorComponent::OnChangeCurrentSlotData(const FMS_SlotData& aSlotDatas)
{
	if (CacheSlotData.CurrentItemTableId == aSlotDatas.CurrentItemTableId
		&& CacheSlotData.CurrentItemAmount == aSlotDatas.CurrentItemAmount)
	{
		return;
	}

	CacheSlotData = aSlotDatas;

	if (CacheSlotData.CurrentItemTableId == INDEX_NONE)
	{
		DestroyChildActor();
		return;
	}

	FMS_ItemData* ItemData = gTableMng.GetTableRowData<FMS_ItemData>(EMS_TableDataType::ItemData, aSlotDatas.CurrentItemTableId);
	MS_ENSURE(ItemData != nullptr);
	
	if (ItemData->ItemType == static_cast<int32>(EMS_ItemType::Money)
		|| ItemData->ItemType == static_cast<int32>(EMS_ItemType::Cash))
	{
		DestroyChildActor();
		
		MS_ENSURE(false);
		return;
	}

	bool bChangeItemTableId = CacheSlotData.CurrentItemTableId != aSlotDatas.CurrentItemTableId;

	// Slot Kind
	if (bChangeItemTableId)
	{
		UClass* SlotClass = UUtilityFunctions::GetClassByTablePathId(ItemData->SlotPath100x100);

		if (IsValid(SlotClass))
		{
			SetChildActorClass(SlotClass);
			CreateChildActor();
		}
	}

	// Slot Item
	AMS_SlotActor* SlotActor = Cast<AMS_SlotActor>(GetChildActor());
	if (!IsValid(SlotActor))
	{
		MS_ENSURE(false);
		return;
	}
	
	SlotActor->OnChangeCurrentSlotData(aSlotDatas, bChangeItemTableId);
}
