#include "Actor/Prop/Furniture/Storage/Pallet/MS_PalletStorage.h"

#include "Component/Actor/Item/MS_StackedBoxComponent.h"

AMS_PalletStorage::AMS_PalletStorage(const FObjectInitializer& aObjectInitializer)
	: Super(aObjectInitializer)
{
	StackedBoxComponent = CreateDefaultSubobject<UMS_StackedBoxComponent>(TEXT("StackedBoxComponent"));
	if (StackedBoxComponent)
	{
		StackedBoxComponent->SetupAttachment(SceneRootComponent);
	}
}

void AMS_PalletStorage::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AMS_PalletStorage::BeginPlay()
{
	Super::BeginPlay();
}

void AMS_PalletStorage::OnChangeRequestSlotDatas(const TArray<FMS_SlotData>& aSlotDatas)
{
	Super::OnChangeRequestSlotDatas(aSlotDatas);
	
	if (StackedBoxComponent)
	{
		StackedBoxComponent->OnChangeRequestSlotDatas(aSlotDatas);
	}
}

void AMS_PalletStorage::OnChangeCurrentSlotDatas(const TArray<FMS_SlotData>& aSlotDatas)
{
	Super::OnChangeCurrentSlotDatas(aSlotDatas);

	if (StackedBoxComponent)
	{
		StackedBoxComponent->OnChangeCurrentSlotDatas(aSlotDatas);
	}
}

void AMS_PalletStorage::SetVisibility(bool bVisibility)
{
	Super::SetVisibility(bVisibility);
	
	if (StackedBoxComponent)
	{
		StackedBoxComponent->SetVisibility(bVisibility);
	}
}
