// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_StackedBoxComponent.h"

#include "MS_Define.h"
#include "Manager_Client/MS_HISMManager.h"


UMS_StackedBoxComponent::UMS_StackedBoxComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	BoxMeshLocations.Emplace(FVector(0.f, 0.f,0.f));
	BoxMeshLocations.Emplace(FVector(0.f, 0.f,80.f));
	BoxMeshLocations.Emplace(FVector(0.f, 0.f,160.f));
	BoxMeshLocations.Emplace(FVector(0.f, 0.f,240.f));
}

void UMS_StackedBoxComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UMS_StackedBoxComponent::OnChangeRequestSlotDatas(const TArray<FMS_SlotData>& aSlotDatas)
{
	CacheSlotDatas = aSlotDatas;
}

void UMS_StackedBoxComponent::OnChangeCurrentSlotDatas(const TArray<FMS_SlotData>& aSlotDatas)
{
	CacheSlotDatas = aSlotDatas;

	UpdateMesh();
}

void UMS_StackedBoxComponent::SetVisibility(bool bVisibility)
{
	bCacheVisibility = bVisibility;

	UpdateMesh();
}

void UMS_StackedBoxComponent::UpdateMesh()
{
	// Visibility == false
	if (!bCacheVisibility)
	{
		if (CacheBoxMeshNum > 0)
		{
			TArray<FVector> RemoveMeshLocations = {};

			for (int32 i = 0; i < CacheBoxMeshNum; ++i)
			{
				if (!BoxMeshLocations.IsValidIndex(i))
				{
					MS_ENSURE(false);
					break;
				}
				
				RemoveMeshLocations.Emplace(GetComponentLocation() + BoxMeshLocations[i]);
			}

			gHISMMng.RemoveInstances(BoxMeshId, RemoveMeshLocations);
			CacheBoxMeshNum = 0;
			return;
		}
	}

	// Visibility == true
	int32 NewBoxMeshNum = 0;
	
	for (const auto& SlotData : CacheSlotDatas)
	{
		if (SlotData.CurrentItemTableId != INDEX_NONE && SlotData.CurrentItemCount > 0)
		{
			++NewBoxMeshNum;
		}
	}

	NewBoxMeshNum = FMath::Min(NewBoxMeshNum, BoxMeshLocations.Num());

	if (NewBoxMeshNum == CacheBoxMeshNum)
	{
		return;
	}

	else if (NewBoxMeshNum < CacheBoxMeshNum)
	{
		TArray<FVector> RemoveMeshLocations = {};

		for (int32 i = NewBoxMeshNum; i < CacheBoxMeshNum; ++i)
		{
			if (!BoxMeshLocations.IsValidIndex(i))
			{
				MS_ENSURE(false);
				break;
			}
				
			RemoveMeshLocations.Emplace(GetComponentLocation() + BoxMeshLocations[i]);
		}

		gHISMMng.RemoveInstances(BoxMeshId, RemoveMeshLocations);
		CacheBoxMeshNum = CacheBoxMeshNum - RemoveMeshLocations.Num();
	}

	else
	{
		TArray<FTransform> AddMeshTransforms = {};

		for (int32 i = CacheBoxMeshNum; i < NewBoxMeshNum; ++i)
		{
			if (!BoxMeshLocations.IsValidIndex(i))
			{
				MS_ENSURE(false);
				break;
			}

			FTransform AddMeshTransform = GetComponentTransform();
			AddMeshTransform.SetLocation(GetComponentLocation() + BoxMeshLocations[i]);
			
			AddMeshTransforms.Emplace(AddMeshTransform);
		}

		gHISMMng.AddInstances(BoxMeshId, AddMeshTransforms);
		CacheBoxMeshNum = CacheBoxMeshNum + AddMeshTransforms.Num();
	}
}

