#include "Actor/Prop/Furniture/Storage/Display/MS_DisplayStorage.h"

AMS_DisplayStorage::AMS_DisplayStorage(const FObjectInitializer& aObjectInitializer)
	: Super(aObjectInitializer)
{
	SlotComponentIndexSize = SlotComponentArray.Add(CreateDefaultSubobject<UMS_StorageSlotComponent>(TEXT("No2StorageSlotComponent")));
	SlotComponentArray[SlotComponentIndexSize]->SetupAttachment(GetRootComponent());
	SlotComponentArray[SlotComponentIndexSize]->SlotOrder = SlotComponentIndexSize;

	SlotComponentIndexSize = SlotComponentArray.Add(CreateDefaultSubobject<UMS_StorageSlotComponent>(TEXT("No3StorageSlotComponent")));
	SlotComponentArray[SlotComponentIndexSize]->SetupAttachment(GetRootComponent());
	SlotComponentArray[SlotComponentIndexSize]->SlotOrder = SlotComponentIndexSize;
}

void AMS_DisplayStorage::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AMS_DisplayStorage::BeginPlay()
{
	Super::BeginPlay();
}