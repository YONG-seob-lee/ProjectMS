#include "Actor/Prop/Furniture/Storage/Pallet/MS_PalletStorage.h"

#include "Component/Prop/Furniture/MS_StorageSlotComponent.h"

AMS_PalletStorage::AMS_PalletStorage(const FObjectInitializer& aObjectInitializer)
	: Super(aObjectInitializer)
{
	/*
	SlotComponentIndexSize = SlotComponentArray.Add(CreateDefaultSubobject<UMS_StorageSlotComponent>(TEXT("No2StorageSlotComponent")));
	SlotComponentArray[SlotComponentIndexSize]->SetupAttachment(SceneRootComponent);
	SlotComponentArray[SlotComponentIndexSize]->SlotOrder = SlotComponentIndexSize;

	SlotComponentIndexSize = SlotComponentArray.Add(CreateDefaultSubobject<UMS_StorageSlotComponent>(TEXT("No3StorageSlotComponent")));
	SlotComponentArray[SlotComponentIndexSize]->SetupAttachment(SceneRootComponent);
	SlotComponentArray[SlotComponentIndexSize]->SlotOrder = SlotComponentIndexSize;

	SlotComponentIndexSize = SlotComponentArray.Add(CreateDefaultSubobject<UMS_StorageSlotComponent>(TEXT("No4StorageSlotComponent")));
	SlotComponentArray[SlotComponentIndexSize]->SetupAttachment(SceneRootComponent);
	SlotComponentArray[SlotComponentIndexSize]->SlotOrder = SlotComponentIndexSize;
	*/
}

void AMS_PalletStorage::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AMS_PalletStorage::BeginPlay()
{
	Super::BeginPlay();
}
