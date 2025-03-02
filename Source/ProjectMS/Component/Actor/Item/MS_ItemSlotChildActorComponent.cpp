// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ItemSlotChildActorComponent.h"

#include "MS_Define.h"
#include "UtilityFunctions.h"
#include "Item/MS_SlotActor.h"
#include "Manager_Both/MS_TableManager.h"
#include "Table/RowBase/MS_ItemData.h"


UMS_ItemSlotChildActorComponent::UMS_ItemSlotChildActorComponent()
	: SlotId(INDEX_NONE)
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UMS_ItemSlotChildActorComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UMS_ItemSlotChildActorComponent::OnChangeRequestSlotData(const FMS_SlotData& aSlotDatas)
{
	if (CacheSlotData.RequestItemTableId == aSlotDatas.RequestItemTableId)
	{
		return;
	}

	CacheSlotData.RequestItemTableId = aSlotDatas.RequestItemTableId;
}

void UMS_ItemSlotChildActorComponent::OnChangeCurrentSlotData(const FMS_SlotData& aSlotDatas)
{
	bool bChangeItemTableId = CacheSlotData.CurrentItemTableId != aSlotDatas.CurrentItemTableId;
	bool bChangeItemCount = CacheSlotData.CurrentItemCount != aSlotDatas.CurrentItemCount;
	
	if (!bChangeItemTableId && !bChangeItemCount)
	{
		return;
	}
	
	CacheSlotData.CurrentItemTableId = aSlotDatas.CurrentItemTableId;
	CacheSlotData.CurrentItemCount = aSlotDatas.CurrentItemCount;

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

	SlotActor->SetVisibility(bCacheVisibility);
	SlotActor->OnChangeCurrentSlotData(aSlotDatas);
}

void UMS_ItemSlotChildActorComponent::SetVisibility(bool bVisibility)
{
	bCacheVisibility = bVisibility;
	
	AMS_SlotActor* SlotActor = Cast<AMS_SlotActor>(GetChildActor());
	if (!IsValid(SlotActor))
	{
		return;
	}

	SlotActor->SetVisibility(bVisibility);
}
