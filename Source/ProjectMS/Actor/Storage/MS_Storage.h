#pragma once

#include "CoreMinimal.h"
#include "Actor/MS_Actor.h"
#include "Component/Storage/MS_StorageAssemblyAreaComponent.h"
#include "Component/Storage/MS_StorageBayComponent.h"
#include "Component/Storage/MS_StorageSlotComponent.h"
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

UCLASS() class PROJECTMS_API AMS_Storage : public AMS_Actor
{
	GENERATED_BODY()
	
public:
	AMS_Storage();

	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float aDeltaTime) override;

	UFUNCTION(BlueprintCallable) TArray<FMS_StorageEachSlotStatus> CheckStorageEachSlotStatus();
	UFUNCTION(BlueprintCallable) FMS_StorageOverallSlotStatus CheckStorageOverallSlotStatus();

	// Component
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TObjectPtr<class USceneComponent> SceneComponent = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TObjectPtr<class UStaticMeshComponent> StorageStaticMeshComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) TObjectPtr<class UMS_StorageAssemblyAreaComponent> StorageAssemblyAreaComponent = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<class UMS_StorageBayComponent*> BayComponentArray = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<class UMS_StorageSlotComponent*> SlotComponentArray = {};

	// Property
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FName StorageRowName = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int SlotComponentIndexSize = INT_MIN;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int BayComponentIndexSize = INT_MIN;
};
