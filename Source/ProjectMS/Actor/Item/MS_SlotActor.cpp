// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_SlotActor.h"

#include "MS_Define.h"
#include "UtilityFunctions.h"
#include "Component/Actor/Item/MS_ItemChildActorComponent.h"
#include "ContentsUtilities/MS_ItemDefine.h"
#include "Table/RowBase/MS_ItemData.h"


struct FMS_ItemData;

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
	
	TArray<UMS_ItemChildActorComponent*> ItemComponents;
	GetComponents<UMS_ItemChildActorComponent>(ItemComponents);

	for (UMS_ItemChildActorComponent* ItemComponent : ItemComponents)
	{
		if (ItemComponent->GetItemOrder() == INDEX_NONE)
		{
			MS_LOG_VERBOSITY(Error, TEXT("[%s] Please set item components order"), *MS_FUNC_STRING);
			MS_ENSURE(false);
		}
		
		ItemOrderToItemComponents.Emplace(ItemComponent->GetItemOrder(), ItemComponent);
	}
}

void AMS_SlotActor::OnChangeCurrentSlotData(const FMS_SlotData& aSlotDatas, bool bChangeItemTableId)
{
	// Kind
	if (bChangeItemTableId)
	{
		for (auto& It : ItemOrderToItemComponents)
		{
			MS_ENSURE(IsValid(It.Value));
			
			if (aSlotDatas.CurrentItemTableId == INDEX_NONE)
			{
				It.Value->DestroyChildActor();
				return;
			}

			FMS_ItemData* ItemData = gTableMng.GetTableRowData<FMS_ItemData>(EMS_TableDataType::ItemData, aSlotDatas.CurrentItemTableId);
			MS_ENSURE(ItemData != nullptr);
	
			if (ItemData->ItemType == static_cast<int32>(EMS_ItemType::Money)
				|| ItemData->ItemType == static_cast<int32>(EMS_ItemType::Cash))
			{
				It.Value->DestroyChildActor();
		
				MS_ENSURE(false);
				return;
			}
			
			UClass* ItemClass = UUtilityFunctions::GetClassByTablePathId(ItemData->PathFile);

			if (IsValid(ItemClass))
			{
				It.Value->SetChildActorClass(ItemClass);
				It.Value->CreateChildActor();
			}
		}
	}

	// Amount
	for (auto& It : ItemOrderToItemComponents)
	{
		MS_ENSURE(IsValid(It.Value));
		
		It.Value->SetItemVisibility(It.Key <= aSlotDatas.CurrentItemAmount);
	}
}
