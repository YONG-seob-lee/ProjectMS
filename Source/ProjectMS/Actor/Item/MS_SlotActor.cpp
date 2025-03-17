// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_SlotActor.h"

#include "MS_Define.h"
#include "Component/Actor/Item/MS_MeshTransformComponent.h"
#include "ContentsUtilities/MS_ItemDefine.h"
#include "Manager_Client/MS_HISMManager.h"
#include "Table/RowBase/MS_ItemData.h"


AMS_SlotActor::AMS_SlotActor(const FObjectInitializer& aObjectInitializer)
	: Super(aObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	ItemAttachedComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ItemAttachedComponent"));
	if (ItemAttachedComponent)
	{
		ItemAttachedComponent->SetupAttachment(SceneRootComponent);
	}
}

void AMS_SlotActor::BeginPlay()
{
	Super::BeginPlay();
}

void AMS_SlotActor::PreInitializeComponents()
{
	Super::PreInitializeComponents();
}

void AMS_SlotActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	TArray<UMS_MeshTransformComponent*> ItemComponents;
	GetComponents<UMS_MeshTransformComponent>(ItemComponents);

	for (UMS_MeshTransformComponent* ItemComponent : ItemComponents)
	{
		if (ItemComponent->GetOrder() == INDEX_NONE)
		{
			MS_ERROR(TEXT("[%s] Please set item components order"), *MS_FUNC_STRING);
			MS_ENSURE(false);
		}
		
		MeshTransformComponents.Emplace(ItemComponent->GetOrder(), ItemComponent);
	}
}

void AMS_SlotActor::OnChangeCurrentSlotData(const FMS_SlotData& aSlotData)
{
	if (bCacheVisibility)
	{
		UpdateMeshes(aSlotData, false);
	}
	
	CacheSlotData = aSlotData;
}

void AMS_SlotActor::SetVisibility(bool bVisibility)
{
	if (bCacheVisibility != bVisibility)
	{
		UpdateMeshes(CacheSlotData, !bVisibility);
		bCacheVisibility = bVisibility;
	}
}

void AMS_SlotActor::UpdateMeshes(FMS_SlotData aSlotData, bool bRemoveAll)
{
	FMS_ItemData* ItemData = gTableMng.GetTableRowData<FMS_ItemData>(EMS_TableDataType::ItemData, aSlotData.CurrentItemTableId);
	
	int32 MeshId = ItemData != nullptr ? ItemData->MeshPath : INDEX_NONE;

	// ===== Remove ===== //
	if (CacheMeshId > 0)
	{
		bool bClear = bRemoveAll || MeshId <= 0 || MeshId != CacheMeshId;

		TArray<FVector> RemoveMeshLocations;
		
		if (bClear)	// 일단 전부 지워야하는 경우
		{
			for (auto& It : MeshTransformComponents)
			{
				if (It.Value->HaveMash())
				{
					RemoveMeshLocations.Emplace(It.Value->GetComponentLocation());
					It.Value->SetHaveMash(false);
				}
			}
		}
	
		else	// 슬롯 데이터보다 많은 수만 지워야 하는 경우
		{
			for (auto& It : MeshTransformComponents)
			{
				if (It.Value->HaveMash())
				{
					if (It.Key >= aSlotData.CurrentItemCount)
					{
						RemoveMeshLocations.Emplace(It.Value->GetComponentLocation());
						It.Value->SetHaveMash(false);
					}
				}
			}
		}

		if (RemoveMeshLocations.Num() > 0)
		{
			gHISMMng.RemoveInstances(CacheMeshId, RemoveMeshLocations);
		}
	}

	// ===== Add ===== //
	if (!bRemoveAll && MeshId > 0)
	{
		TArray<FTransform> AddMeshTransforms;
		
		for (auto& It : MeshTransformComponents)
		{
			if (!It.Value->HaveMash())
			{
				if (It.Key < aSlotData.CurrentItemCount)
				{
					AddMeshTransforms.Emplace(It.Value->GetComponentTransform());
					It.Value->SetHaveMash(true);
				}
			}
		}

		if (AddMeshTransforms.Num() > 0)
		{
			gHISMMng.AddInstances(MeshId, AddMeshTransforms);
		}
	}

	CacheMeshId = MeshId;
}
