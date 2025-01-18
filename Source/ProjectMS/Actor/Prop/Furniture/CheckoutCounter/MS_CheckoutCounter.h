#pragma once

#include "CoreMinimal.h"
#include "Actor/Prop/Furniture/MS_Furniture.h"
#include "MS_CheckoutCounter.generated.h"

UCLASS() class PROJECTMS_API AMS_CheckoutCounter : public AMS_Furniture
{
	GENERATED_BODY()
	
public:
	AMS_CheckoutCounter();

	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float aDeltaTime) override;
	
	// Component
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TObjectPtr<class USceneComponent> SceneComponent = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) class UBoxComponent* CollisionBoxComponent = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TObjectPtr<class UStaticMeshComponent> StaticMeshComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) TObjectPtr<class UMS_StorageAssemblyAreaComponent> StorageAssemblyAreaComponent = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<class UMS_StorageBayComponent*> BayComponentArray = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<class UMS_StorageSlotComponent*> SlotComponentArray = {};

	// Property
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FName CheckoutCounterName = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int SlotComponentIndexSize = INT_MIN;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int BayComponentIndexSize = INT_MIN;
};
