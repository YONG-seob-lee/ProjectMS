#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "MS_StorageOperationSpotComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) ) class PROJECTMS_API UMS_StorageOperationSpotComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:	
	UMS_StorageOperationSpotComponent();

	virtual void InitializeComponent() override;
#if WITH_EDITOR
	virtual void OnComponentCreated() override;
	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;
	virtual void OnRegister() override;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void PostEditComponentMove(bool bFinished) override;
	virtual void PostEditUndo() override;

private:
	void DrawSpotOutline();
	void RedrawSpotOutline();
	void EraseSpotOutline();

	void DrawAssemblyAreaOutline();
	void RedrawAssemblyAreaOutline();
	void EraseAssemblyAreaOutline();
#endif

	UFUNCTION(BlueprintCallable) void ReserveWorker(class AMS_StaffAICharacter* aStaffCharacter);
	UFUNCTION(BlueprintCallable) void UnreserveWorker();
	UFUNCTION(BlueprintCallable) void DeployWorker(class AMS_StaffAICharacter* aStaffCharacter);
	UFUNCTION(BlueprintCallable) void UndeployWorker();

	// Instance
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TObjectPtr<class AMS_Prop_Storage> OwnerStorage = nullptr;

	// Property
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int SpotOrder = INT_MIN;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FVector SpotSize = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FColor SpotOutlineColor = FColor::Purple;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float SpotOutlineThickness = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) FVector AssemblyAreaSize = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FColor AssemblyAreaOutlineColor = FColor::Turquoise;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float AssemblyAreaOutlineThickness = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool OccupancyFlag = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TObjectPtr<class AMS_StaffAICharacter> OccupancyWorker = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool ReservationFlag = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TObjectPtr<class AMS_StaffAICharacter> ReservationWorker = nullptr;
};
