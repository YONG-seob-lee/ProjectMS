#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "MS_StorageSlotComponent.generated.h"

UCLASS() class PROJECTMS_API UMS_StorageSlotComponent : public UStaticMeshComponent
{
	GENERATED_BODY()


public:
	UMS_StorageSlotComponent(const FObjectInitializer& ObjectInitializer);

#if WITH_EDITOR
	virtual void OnComponentCreated() override;
	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;
	virtual void OnRegister() override;
	virtual void InitializeComponent() override;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void PostEditComponentMove(bool bFinished) override;
	virtual void PostEditUndo() override;

private:
	void DrawSlotOutline();
	void RedrawSlotOutline();
	void EraseSlotOutline();
#endif

public:
	UFUNCTION(BlueprintCallable) void ReserveWorker(class AMS_StaffAICharacter* aTarget);
	UFUNCTION(BlueprintCallable) void UnreserveWorker();
	UFUNCTION(BlueprintCallable) bool LoadStuff(FName aStuffRowName, int aStockQuantity);
	UFUNCTION(BlueprintCallable) void UnloadStuff();

	UFUNCTION(BlueprintCallable) void AdjustSlotStock(const FName& aStuffRowName, const int& aStockQuantity, const int& aStockCapacity);

	// Property
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int SlotOrder = INT_MIN;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FVector SlotSize = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FColor SlotOutlineColor = FColor::Cyan;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float SlotOutlineThickness = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) FName StuffRowName = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int StockQuantity = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int StockCapacity = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool ReservationFlag = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) class AMS_StaffAICharacter* ReservationWorker = nullptr;

	// Instance
public:
	class AMS_Storage* OwnerInst = nullptr;
};
