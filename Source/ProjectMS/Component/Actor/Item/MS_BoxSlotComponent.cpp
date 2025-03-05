// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_BoxSlotComponent.h"

#include "Manager_Client/MS_HISMManager.h"


UMS_BoxSlotComponent::UMS_BoxSlotComponent()
	: SlotId(INDEX_NONE)
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UMS_BoxSlotComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UMS_BoxSlotComponent::OnChangeRequestSlotData(const FMS_SlotData& aSlotDatas)
{
	if (CacheSlotData.RequestItemTableId == aSlotDatas.RequestItemTableId)
	{
		return;
	}

	CacheSlotData.RequestItemTableId = aSlotDatas.RequestItemTableId;
}

void UMS_BoxSlotComponent::OnChangeCurrentSlotData(const FMS_SlotData& aSlotDatas)
{
	bool bChangeItemTableId = CacheSlotData.CurrentItemTableId != aSlotDatas.CurrentItemTableId;
	bool bChangeItemCount = CacheSlotData.CurrentItemCount != aSlotDatas.CurrentItemCount;
	
	if (!bChangeItemTableId && !bChangeItemCount)
	{
		return;
	}
	
	CacheSlotData.CurrentItemTableId = aSlotDatas.CurrentItemTableId;
	CacheSlotData.CurrentItemCount = aSlotDatas.CurrentItemCount;

	UpdateMesh();
}

void UMS_BoxSlotComponent::SetVisibility(bool bVisibility)
{
	bCacheVisibility = bVisibility;

	UpdateMesh();
}

void UMS_BoxSlotComponent::UpdateMesh()
{
	if (CacheSlotData.CurrentItemTableId == INDEX_NONE || CacheSlotData.CurrentItemCount == 0 || !bCacheVisibility)
	{
		if (bHaveMash)
		{
			gHISMMng.RemoveInstance(MeshId::BoxMeshId, GetComponentLocation());
			bHaveMash = false;
		}
	}

	else
	{
		if (!bHaveMash)
		{
			gHISMMng.AddInstance(MeshId::BoxMeshId, GetComponentTransform());
			bHaveMash = true;
		}
	}
}
