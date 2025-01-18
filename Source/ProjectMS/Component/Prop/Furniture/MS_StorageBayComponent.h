#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "MS_StorageBayComponent.generated.h"

UCLASS(Meta = (DisplayName = "StorageBayComponent")) class PROJECTMS_API UMS_StorageBayComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UMS_StorageBayComponent(const FObjectInitializer& ObjectInitializer);

#if WITH_EDITOR
	virtual void OnComponentCreated() override;
	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;
	virtual void OnRegister() override;
	virtual void InitializeComponent() override;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void PostEditComponentMove(bool bFinished) override;
	virtual void PostEditUndo() override;

private:
	void DrawBayOutline();
	void RedrawBayOutline();
	void EraseBayOutline();
#endif

public:
	UFUNCTION(BlueprintCallable) void ReserveWorker(class AMS_StaffAICharacter* aTarget);
	UFUNCTION(BlueprintCallable) void UnreserveWorker();
	UFUNCTION(BlueprintCallable) void DeployWorker(class AMS_StaffAICharacter* aTarget);
	UFUNCTION(BlueprintCallable) void UndeployWorker();

	// Property
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int BayOrder = INT_MIN;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FVector BaySize = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FColor BayOutlineColor = FColor::Purple;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float BayOutlineThickness = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool OccupancyFlag = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) class AMS_StaffAICharacter* OccupancyWorker = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool ReservationFlag = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) class AMS_StaffAICharacter* ReservationWorker = nullptr;

	// Instance
public:
	class AMS_Storage* OwnerStorage = nullptr;
};
