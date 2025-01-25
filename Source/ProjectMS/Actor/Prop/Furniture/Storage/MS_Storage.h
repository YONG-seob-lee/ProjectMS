#pragma once

#include "CoreMinimal.h"
#include "Actor/Prop/Furniture/MS_Furniture.h"
#include "Component/Prop/Furniture/MS_StorageAssemblyAreaComponent.h"
#include "Component/Prop/Furniture/MS_StorageBayComponent.h"
#include "Component/Prop/Furniture/MS_StorageSlotComponent.h"
#include "MS_Storage.generated.h"

USTRUCT(BlueprintType) struct FMS_StorageEachSlotStatus
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int SlotOrder = INT_MIN;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FName StuffRowName = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int StockQuantity = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int StockCapacity = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool ReservationFlag = false;
};

USTRUCT(BlueprintType) struct FMS_StorageOverallSlotStatus
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int OccupiedSlotCount = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int ReservedSlotCount = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int UnoccupiedSlotCount = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap<FName, int> StuffStockMap = {};
};

UCLASS() class PROJECTMS_API AMS_Storage : public AMS_Furniture
{
	GENERATED_BODY()
	
public:
	AMS_Storage(const FObjectInitializer& aObjectInitializer);

	virtual void PostInitializeComponents() override;

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable) TArray<FMS_StorageEachSlotStatus> CheckStorageEachSlotStatus();
	UFUNCTION(BlueprintCallable) FMS_StorageOverallSlotStatus CheckStorageOverallSlotStatus();

	UFUNCTION() void AddCharacterToStorageReservationArray(class AMS_AICharacter* aCharacter);
	UFUNCTION() void RemoveCharacterFromStorageReservationArray(class AMS_AICharacter* aCharacter);

	// Component
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) class UBoxComponent* CollisionBoxComponent = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TObjectPtr<class UMS_StorageAssemblyAreaComponent> StorageAssemblyAreaComponent = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<class UMS_StorageBayComponent*> BayComponentArray = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<class UMS_StorageSlotComponent*> SlotComponentArray = {};

	// Property
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FName StorageName = {};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 SlotComponentIndexSize = INT_MIN;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 BayComponentIndexSize = INT_MIN;
	
	UPROPERTY(EDitAnywhere, BlueprintReadWrite) TArray<class AMS_AICharacter*> ReservedAICharacterArray = {};
};