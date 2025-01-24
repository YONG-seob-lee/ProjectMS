#pragma once

#include "CoreMinimal.h"
#include "Actor/Prop/Furniture/MS_Furniture.h"
#include "MS_Storage.generated.h"

UCLASS()
class PROJECTMS_API AMS_Storage : public AMS_Furniture
{
	GENERATED_BODY()
	
public:
	AMS_Storage(const FObjectInitializer& aObjectInitializer);
	
	virtual void PreInitializeComponents() override;
	
	virtual void PostInitializeComponents() override;

protected:
	virtual void BeginPlay() override;

	
public:
	UFUNCTION(BlueprintCallable)
	TArray<FMS_StorageEachSlotStatus> GetStorageEachSlotStatus();
	
	UFUNCTION(BlueprintCallable)
	FMS_StorageOverallSlotStatus GetStorageOverallSlotStatus();

	UFUNCTION()
	void AddCharacterToStorageReservationArray(class AMS_AICharacter* aCharacter);
	
	UFUNCTION()
	void RemoveCharacterFromStorageReservationArray(class AMS_AICharacter* aCharacter);

	 	
	// Component : Getter
	TObjectPtr<class UMS_StorageAssemblyAreaComponent> GetStorageAssemblyAreaComponent() const { return StorageAssemblyAreaComponent; }

	const TArray<TObjectPtr<class UMS_StorageBayComponent>>& GetBayComponentArray() const { return BayComponentArray; }
	TObjectPtr<class UMS_StorageBayComponent> GetBayComponent(int32 aIndex) const;
	int32 GetBayComponentNum() const { return BayComponentArray.Num(); }

	const TArray<TObjectPtr<class UMS_StorageSlotComponent>>& GetSlotComponentArray() const { return SlotComponentArray; }
	TObjectPtr<UMS_StorageSlotComponent> GetSlotComponent(int32 aIndex) const;
	int32 GetSlotComponentNum() const { return SlotComponentArray.Num(); }

	
	// Property : Getter
	TArray<TWeakObjectPtr<class AMS_AICharacter>> GetReservedAICharacterArray(bool bCleanUp = true);
	bool HasReservedAICharacter(bool bCleanUp = true);
	
	void CleanUpReservedAICharacterArray();

	
	// Component
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UMS_StorageAssemblyAreaComponent> StorageAssemblyAreaComponent = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<UMS_StorageBayComponent>> BayComponentArray = {};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<UMS_StorageSlotComponent>> SlotComponentArray = {};

	
	// Property
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName StorageName = {};
	
	UPROPERTY()
	TArray<TWeakObjectPtr<class AMS_AICharacter>> ReservedAICharacterArray;
};
