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

void UMS_ItemSlotChildActorComponent::OnChangeRequestSlotData(const FMS_SlotData& aSlotData)
{
	if (CacheSlotData.RequestItemTableId == aSlotData.RequestItemTableId)
	{
		return;
	}

	CacheSlotData.RequestItemTableId = aSlotData.RequestItemTableId;
}

void UMS_ItemSlotChildActorComponent::OnChangeCurrentSlotData(const FMS_SlotData& aSlotData)
{
	bool bChangeItemTableId = CacheSlotData.CurrentItemTableId != aSlotData.CurrentItemTableId;
	bool bChangeItemCount = CacheSlotData.CurrentItemCount != aSlotData.CurrentItemCount;
	
	if (!bChangeItemTableId && !bChangeItemCount)
	{
		return;
	}
	
	CacheSlotData.CurrentItemTableId = aSlotData.CurrentItemTableId;
	CacheSlotData.CurrentItemCount = aSlotData.CurrentItemCount;

	if (CacheSlotData.CurrentItemTableId == INDEX_NONE)
	{
		AMS_SlotActor* SlotActor = Cast<AMS_SlotActor>(GetChildActor());
		if (IsValid(SlotActor))
		{
			SlotActor->OnChangeCurrentSlotData(aSlotData);
			DestroyChildActor();
			
			return;
		}
	}

	FMS_ItemData* ItemData = gTableMng.GetTableRowData<FMS_ItemData>(EMS_TableDataType::ItemData, aSlotData.CurrentItemTableId);
	MS_ENSURE(ItemData != nullptr);
	
	if (ItemData->ItemType == static_cast<int32>(EMS_ItemType::Money)
		|| ItemData->ItemType == static_cast<int32>(EMS_ItemType::Cash))
	{
		AMS_SlotActor* SlotActor = Cast<AMS_SlotActor>(GetChildActor());
		if (IsValid(SlotActor))
		{
			SlotActor->OnChangeCurrentSlotData(aSlotData);
			DestroyChildActor();
		
			MS_ENSURE(false);
			return;
		}
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
	SlotActor->OnChangeCurrentSlotData(aSlotData);
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
