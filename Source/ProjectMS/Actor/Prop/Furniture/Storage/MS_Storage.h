#pragma once

#include "CoreMinimal.h"
#include "Actor/Prop/Furniture/MS_Furniture.h"
#include "MS_Storage.generated.h"

UCLASS() class PROJECTMS_API AMS_Storage : public AMS_Furniture
{
	GENERATED_BODY()
	
public:
	AMS_Storage(const FObjectInitializer& aObjectInitializer);

	virtual void PostInitializeComponents() override;

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	TArray<FMS_StorageEachSlotStatus> CheckStorageEachSlotStatus();
	
	UFUNCTION(BlueprintCallable)
	FMS_StorageOverallSlotStatus CheckStorageOverallSlotStatus();

	UFUNCTION()
	void AddCharacterToStorageReservationArray(class AMS_AICharacter* aCharacter);
	
	UFUNCTION()
	void RemoveCharacterFromStorageReservationArray(class AMS_AICharacter* aCharacter);

	// Component
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* CollisionBoxComponent = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UMS_StorageAssemblyAreaComponent> StorageAssemblyAreaComponent = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class UMS_StorageBayComponent*> BayComponentArray = {};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class UMS_StorageSlotComponent*> SlotComponentArray = {};

	// Property
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName StorageName = {};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SlotComponentIndexSize = INT_MIN;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BayComponentIndexSize = INT_MIN;
	
	UPROPERTY(EDitAnywhere, BlueprintReadWrite)
	TArray<class AMS_AICharacter*> ReservedAICharacterArray = {};
};
