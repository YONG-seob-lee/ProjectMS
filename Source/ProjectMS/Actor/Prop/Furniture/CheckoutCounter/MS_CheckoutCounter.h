#pragma once

#include "CoreMinimal.h"
#include "Actor/Prop/Furniture/MS_Furniture.h"
#include "MS_CheckoutCounter.generated.h"

UCLASS() class PROJECTMS_API AMS_CheckoutCounter : public AMS_Furniture
{
	GENERATED_BODY()
	
public:
	AMS_CheckoutCounter(const FObjectInitializer& aObjectInitializer);

	virtual void PostInitializeComponents() override;
	
protected:
	virtual void BeginPlay() override;
	
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
	FName CheckoutCounterName = {};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SlotComponentIndexSize = INT_MIN;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BayComponentIndexSize = INT_MIN;
};
