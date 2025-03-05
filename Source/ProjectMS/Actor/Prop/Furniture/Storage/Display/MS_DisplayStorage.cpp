#include "Actor/Prop/Furniture/Storage/Display/MS_DisplayStorage.h"

#include "Component/Actor/Item/MS_ItemSlotChildActorComponent.h"


AMS_DisplayStorage::AMS_DisplayStorage(const FObjectInitializer& aObjectInitializer)
	: Super(aObjectInitializer)
{
	ItemSlotAttachedComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SlotAttachedComponent"));
	if (ItemSlotAttachedComponent)
	{
		ItemSlotAttachedComponent->SetupAttachment(SceneRootComponent);
	}
}

void AMS_DisplayStorage::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	TArray<UMS_ItemSlotChildActorComponent*> SlotComponents;
	GetComponents<UMS_ItemSlotChildActorComponent>(SlotComponents);

	for (UMS_ItemSlotChildActorComponent* SlotComponent : SlotComponents)
	{
		if (SlotComponent->GetSlotId() == INDEX_NONE)
		{
			MS_LOG_VERBOSITY(Error, TEXT("[%s] Please set slot components order"), *MS_FUNC_STRING);
			MS_ENSURE(false);
		}
		
		SlotIdToItemSlotComponents.Emplace(SlotComponent->GetSlotId(), SlotComponent);
	}
}

void AMS_DisplayStorage::BeginPlay()
{
	Super::BeginPlay();
}

void AMS_DisplayStorage::OnChangeRequestSlotDatas(const TArray<FMS_SlotData>& aSlotDatas, const TArray<int32>& aChangeSlotIds)
{
	Super::OnChangeRequestSlotDatas(aSlotDatas, aChangeSlotIds);

	for (auto& It : SlotIdToItemSlotComponents)
	{
		if (aSlotDatas.IsValidIndex(It.Key))
		{
			It.Value->OnChangeRequestSlotData(aSlotDatas[It.Key]);
		}
		else
		{
			It.Value->OnChangeRequestSlotData(FMS_SlotData());
		}
	}
}

void AMS_DisplayStorage::OnChangeCurrentSlotDatas(const TArray<FMS_SlotData>& aSlotDatas, const TArray<int32>& aChangeSlotIds)
{
	Super::OnChangeCurrentSlotDatas(aSlotDatas, aChangeSlotIds);

	for (auto& It : SlotIdToItemSlotComponents)
	{
		if (aSlotDatas.IsValidIndex(It.Key))
		{
			It.Value->OnChangeCurrentSlotData(aSlotDatas[It.Key]);
		}
		else
		{
			It.Value->OnChangeCurrentSlotData(FMS_SlotData());
		}
	}
}

void AMS_DisplayStorage::SetVisibility(bool bVisibility)
{
	Super::SetVisibility(bVisibility);

	if (!IsPreviewProp())
	{
		for (auto& It : SlotIdToItemSlotComponents)
		{
			if (It.Value != nullptr)
			{
				It.Value->SetVisibility(bVisibility);
			}
		}
	}
}
