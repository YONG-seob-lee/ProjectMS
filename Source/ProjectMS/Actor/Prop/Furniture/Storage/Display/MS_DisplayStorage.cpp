#include "Actor/Prop/Furniture/Storage/Display/MS_DisplayStorage.h"

#include "Component/Prop/Furniture/MS_StorageSlotComponent.h"

AMS_DisplayStorage::AMS_DisplayStorage(const FObjectInitializer& aObjectInitializer)
	: Super(aObjectInitializer)
{
	SlotComponentIndexSize = SlotComponentArray.Add(CreateDefaultSubobject<UMS_StorageSlotComponent>(TEXT("No2StorageSlotComponent")));
	SlotComponentArray[SlotComponentIndexSize]->SetupAttachment(SceneRootComponent);
	SlotComponentArray[SlotComponentIndexSize]->SlotOrder = SlotComponentIndexSize;

	SlotComponentIndexSize = SlotComponentArray.Add(CreateDefaultSubobject<UMS_StorageSlotComponent>(TEXT("No3StorageSlotComponent")));
	SlotComponentArray[SlotComponentIndexSize]->SetupAttachment(SceneRootComponent);
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