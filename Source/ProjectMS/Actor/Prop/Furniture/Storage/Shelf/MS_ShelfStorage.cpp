#include "Actor/Prop/Furniture/Storage/Shelf/MS_ShelfStorage.h"

#include "Component/Actor/Item/MS_BoxSlotComponent.h"

AMS_ShelfStorage::AMS_ShelfStorage(const FObjectInitializer& aObjectInitializer)
	: Super(aObjectInitializer)
{
	BoxSlotAttachedComponent = CreateDefaultSubobject<USceneComponent>(TEXT("BoxSlotAttachedComponent"));
	if (BoxSlotAttachedComponent)
	{
		BoxSlotAttachedComponent->SetupAttachment(SceneRootComponent);
	}
}

void AMS_ShelfStorage::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	TArray<UMS_BoxSlotComponent*> SlotComponents;
	GetComponents<UMS_BoxSlotComponent>(SlotComponents);

	for (UMS_BoxSlotComponent* SlotComponent : SlotComponents)
	{
		if (SlotComponent->GetSlotId() == INDEX_NONE)
		{
			MS_LOG_VERBOSITY(Error, TEXT("[%s] Please set slot components order"), *MS_FUNC_STRING);
			MS_ENSURE(false);
		}
		
		SlotIdToBoxSlotComponents.Emplace(SlotComponent->GetSlotId(), SlotComponent);
	}
}

void AMS_ShelfStorage::BeginPlay()
{
	Super::BeginPlay();
}

void AMS_ShelfStorage::OnChangeRequestSlotDatas(const TArray<FMS_SlotData>& aSlotDatas)
{
	Super::OnChangeRequestSlotDatas(aSlotDatas);

	for (auto& It : SlotIdToBoxSlotComponents)
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

void AMS_ShelfStorage::OnChangeCurrentSlotDatas(const TArray<FMS_SlotData>& aSlotDatas)
{
	Super::OnChangeCurrentSlotDatas(aSlotDatas);

	for (auto& It : SlotIdToBoxSlotComponents)
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

void AMS_ShelfStorage::SetVisibility(bool bVisibility)
{
	Super::SetVisibility(bVisibility);
	
	if (!IsPreviewProp())
	{
		for (auto& It : SlotIdToBoxSlotComponents)
		{
			if (It.Value != nullptr)
			{
				It.Value->SetVisibility(bVisibility);
			}
		}
	}
}
