// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_BoxSlotComponent.h"

#include "Manager_Client/MS_HISMManager.h"


UMS_BoxSlotComponent::UMS_BoxSlotComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UMS_BoxSlotComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UMS_BoxSlotComponent::OnChangeRequestSlotData(const FMS_SlotData& aSlotData)
{
	CacheSlotData = aSlotData;
}

void UMS_BoxSlotComponent::OnChangeCurrentSlotData(const FMS_SlotData& aSlotData)
{
	CacheSlotData = aSlotData;

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
			gHISMMng.RemoveInstance(BoxMeshId, GetComponentLocation());
			bHaveMash = false;
		}
	}

	else
	{
		if (!bHaveMash)
		{
			gHISMMng.AddInstance(BoxMeshId, GetComponentTransform());
			bHaveMash = true;
		}
	}
}
