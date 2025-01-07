#include "Actor/Storage/MS_Storage.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

AMS_Storage::AMS_Storage()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);

	StorageStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StorageStaticMeshComponent"));
	StorageStaticMeshComponent->SetupAttachment(GetRootComponent());
	StorageStaticMeshComponent->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));

	StorageAssemblyAreaComponent = CreateDefaultSubobject<UMS_StorageAssemblyAreaComponent>(TEXT("StorageAssemblyAreaComponent"));
	StorageAssemblyAreaComponent->SetupAttachment(GetRootComponent());
	StorageAssemblyAreaComponent->SetRelativeLocation(FVector(-100.0f, 0.0f, 0.0f));

	BayComponentIndexSize = BayComponentArray.Add(CreateDefaultSubobject<UMS_StorageBayComponent>(TEXT("No1StorageBayComponent")));
	BayComponentArray[BayComponentIndexSize]->SetupAttachment(GetRootComponent());
	BayComponentArray[BayComponentIndexSize]->SetRelativeLocation(FVector(-100.0f, 0.0f, 0.0f));
	BayComponentArray[BayComponentIndexSize]->BayOrder = BayComponentIndexSize;

	SlotComponentIndexSize = SlotComponentArray.Add(CreateDefaultSubobject<UMS_StorageSlotComponent>(TEXT("No1StorageSlotComponent")));
	SlotComponentArray[SlotComponentIndexSize]->SetupAttachment(GetRootComponent());
	SlotComponentArray[SlotComponentIndexSize]->SlotOrder = SlotComponentIndexSize;
}

void AMS_Storage::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AMS_Storage::BeginPlay()
{
	Super::BeginPlay();
}

void AMS_Storage::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
}

TArray<FMS_StorageEachSlotStatus> AMS_Storage::CheckStorageEachSlotStatus()
{
	TArray<UMS_StorageSlotComponent*> StorageSlotComponentArray = {};
	GetComponents<UMS_StorageSlotComponent>(StorageSlotComponentArray);
	TArray<FMS_StorageEachSlotStatus> StorageEachSlotStatusArray = {};
	for (int i = 0; i < StorageSlotComponentArray.Num(); ++i)
	{
		StorageEachSlotStatusArray.Add(
			FMS_StorageEachSlotStatus{
				.SlotOrder = StorageSlotComponentArray[i]->SlotOrder,
				.StuffRowName = StorageSlotComponentArray[i]->StuffRowName,
				.StockQuantity = StorageSlotComponentArray[i]->StockQuantity,
				.StockCapacity = StorageSlotComponentArray[i]->StockCapacity,
				.ReservationFlag = StorageSlotComponentArray[i]->ReservationFlag
			}
		);
	}

	return StorageEachSlotStatusArray;
}

FMS_StorageOverallSlotStatus AMS_Storage::CheckStorageOverallSlotStatus()
{
	TArray<UMS_StorageSlotComponent*> StorageSlotComponentArray = {};
	GetComponents<UMS_StorageSlotComponent>(StorageSlotComponentArray);
	FMS_StorageOverallSlotStatus StorageOverallSlotStatus = {};
	StorageOverallSlotStatus.OccupiedSlotCount = StorageOverallSlotStatus.UnoccupiedSlotCount = 0;
	for (int i = 0; i < StorageSlotComponentArray.Num(); ++i)
	{
		if (StorageSlotComponentArray[i]->ReservationFlag == true)
			StorageOverallSlotStatus.ReservedSlotCount += 1;
		else if (StorageSlotComponentArray[i]->StuffRowName == NAME_None)
			StorageOverallSlotStatus.UnoccupiedSlotCount += 1;
		else
			StorageOverallSlotStatus.OccupiedSlotCount += 1;

		if (StorageOverallSlotStatus.StuffStockMap.Contains(StorageSlotComponentArray[i]->StuffRowName) == true)
			StorageOverallSlotStatus.StuffStockMap[StorageSlotComponentArray[i]->StuffRowName] += StorageSlotComponentArray[i]->StockQuantity;
		else
			StorageOverallSlotStatus.StuffStockMap.Add(StorageSlotComponentArray[i]->StuffRowName, StorageSlotComponentArray[i]->StockQuantity);
	}

	return StorageOverallSlotStatus;
}
