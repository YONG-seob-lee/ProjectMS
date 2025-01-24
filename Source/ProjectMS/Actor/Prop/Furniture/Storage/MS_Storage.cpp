#include "Actor/Prop/Furniture/Storage/MS_Storage.h"

#include "Character/AICharacter/MS_AICharacter.h"
#include "Component/Prop/Furniture/MS_StorageAssemblyAreaComponent.h"
#include "Component/Prop/Furniture/MS_StorageBayComponent.h"
#include "Component/Prop/Furniture/MS_StorageSlotComponent.h"


AMS_Storage::AMS_Storage(const FObjectInitializer& aObjectInitializer)
	: Super(aObjectInitializer)
{
	if (ShapeCollisionComponent)
	{
		ShapeCollisionComponent->SetCollisionProfileName(TEXT("StorageCollisionPreset"));
	}

	StorageAssemblyAreaComponent = CreateDefaultSubobject<UMS_StorageAssemblyAreaComponent>(TEXT("StorageAssemblyAreaComponent"));
	if (StorageAssemblyAreaComponent)
	{
		StorageAssemblyAreaComponent->SetupAttachment(SceneRootComponent);
		StorageAssemblyAreaComponent->SetRelativeLocation(FVector(-150.0f, 0.0f, 0.0f));
	}
}

void AMS_Storage::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	// Component
	GetComponents<UMS_StorageBayComponent>(BayComponentArray);
	GetComponents<UMS_StorageSlotComponent>(SlotComponentArray);
}

void AMS_Storage::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AMS_Storage::BeginPlay()
{
	Super::BeginPlay();
}

TArray<FMS_StorageEachSlotStatus> AMS_Storage::GetStorageEachSlotStatus()
{
	TArray<FMS_StorageEachSlotStatus> StorageEachSlotStatusArray = {};
	
	for (int i = 0; i < SlotComponentArray.Num(); ++i)
	{
		if (!IsValid(SlotComponentArray[i]))
		{
			MS_LOG_Verbosity(Error, TEXT("[%s] Slot component is invaild [Index : %d]"), *MS_FUNC_STRING, i);
			MS_Ensure(false);

			// Add Empty
			StorageEachSlotStatusArray.Add(FMS_StorageEachSlotStatus{});
		}
		
		StorageEachSlotStatusArray.Add(
			FMS_StorageEachSlotStatus{
				.SlotOrder = SlotComponentArray[i]->SlotOrder,
				.StuffRowName = SlotComponentArray[i]->StuffRowName,
				.StockQuantity = SlotComponentArray[i]->StockQuantity,
				.StockCapacity = SlotComponentArray[i]->StockCapacity,
				.ReservationFlag = SlotComponentArray[i]->ReservationFlag
			}
		);
	}

	return StorageEachSlotStatusArray;
}

FMS_StorageOverallSlotStatus AMS_Storage::GetStorageOverallSlotStatus()
{
	FMS_StorageOverallSlotStatus StorageOverallSlotStatus = {};
	StorageOverallSlotStatus.OccupiedSlotCount = StorageOverallSlotStatus.UnoccupiedSlotCount = 0;
	
	for (int i = 0; i < SlotComponentArray.Num(); ++i)
	{
		if (!IsValid(SlotComponentArray[i]))
		{
			MS_LOG_Verbosity(Error, TEXT("[%s] Slot component is invaild [Index : %d]"), *MS_FUNC_STRING, i);
			MS_Ensure(false);

			// To Do : 문제가 생겼을 때 어떻게 처리해야하는지 확인
			continue;
		}
		
		if (SlotComponentArray[i]->ReservationFlag == true)
			StorageOverallSlotStatus.ReservedSlotCount += 1;
		else if (SlotComponentArray[i]->StuffRowName == NAME_None)
			StorageOverallSlotStatus.UnoccupiedSlotCount += 1;
		else
			StorageOverallSlotStatus.OccupiedSlotCount += 1;

		if (StorageOverallSlotStatus.StuffStockMap.Contains(SlotComponentArray[i]->StuffRowName) == true)
			StorageOverallSlotStatus.StuffStockMap[SlotComponentArray[i]->StuffRowName] += SlotComponentArray[i]->StockQuantity;
		else
			StorageOverallSlotStatus.StuffStockMap.Add(SlotComponentArray[i]->StuffRowName, SlotComponentArray[i]->StockQuantity);
	}

	return StorageOverallSlotStatus;
}

void AMS_Storage::AddCharacterToStorageReservationArray(AMS_AICharacter* aCharacter)
{
	if (IsValid(aCharacter))
	{
		if (ReservedAICharacterArray.Contains(aCharacter) == false)
		{
			ReservedAICharacterArray.Add(aCharacter);
		}
	}
}

void AMS_Storage::RemoveCharacterFromStorageReservationArray(AMS_AICharacter* aCharacter)
{
	if (IsValid(aCharacter))
	{
		if (ReservedAICharacterArray.Contains(aCharacter) == true)
		{
			ReservedAICharacterArray.Remove(aCharacter);
		}
	}
}

TObjectPtr<UMS_StorageBayComponent> AMS_Storage::GetBayComponent(int32 aIndex) const
{
	if (BayComponentArray.IsValidIndex(aIndex))
	{
		return BayComponentArray[aIndex];
	}

	return nullptr;
}

TObjectPtr<UMS_StorageSlotComponent> AMS_Storage::GetSlotComponent(int32 aIndex) const
{
	if (SlotComponentArray.IsValidIndex(aIndex))
	{
		return SlotComponentArray[aIndex];
	}

	return nullptr;
}

TArray<TWeakObjectPtr<AMS_AICharacter>> AMS_Storage::GetReservedAICharacterArray(bool bCleanUp /* = true */)
{
	if (bCleanUp)
	{
		CleanUpReservedAICharacterArray();
	}
	
	return ReservedAICharacterArray;
}

bool AMS_Storage::HasReservedAICharacter(bool bCleanUp)
{
	if (bCleanUp)
	{
		CleanUpReservedAICharacterArray();
	}
	
	return ReservedAICharacterArray.Num() == 0;
}

void AMS_Storage::CleanUpReservedAICharacterArray()
{
	ReservedAICharacterArray.RemoveAll([] (const TWeakObjectPtr<AMS_AICharacter> Character)
	{
		return Character == nullptr;
	});
}
