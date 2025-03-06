// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Mode/ModeObject/Supervisor/MS_AISupervisor.h"
#include "MS_CustomerSupervisor.generated.h"

namespace Customer
{
	constexpr int32 SpawnMaxUnitCount = 10;
	constexpr int32 SpawnMaxTime = 8.f;
}
/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_CustomerSupervisor : public UMS_AISupervisor
{
	GENERATED_BODY()

public:
	UMS_CustomerSupervisor();
	
	virtual void Initialize() override;
	virtual void Finalize() override;

	virtual void Tick(float aDeltaTime) override;
	
	virtual void Begin() override;
	virtual void Exit() override;

	
	virtual void UpdateMinute(int32 aCurrentMinute) override;
	virtual void UpdateScheduleEvent(int32 aScheduleEvent) override;

	bool SpawnCustomer();
	bool DestroyCustomer(class UMS_CustomerAIUnit* aDestroyAIUnit);
	
protected:
	void StartCustomerSpawn();
	void StopCustomerSpawn();
	
	void GetRandomSpawnPoint(FVector& SpawnLocation, FRotator& SpawnRotator);
	
private:
	void InitCustomerSpawnPoint();
	void CashingDuckSplineActors() const;
	
	bool bStartCustomerSpawn = false;
	float SpawnIntervalDelayTime = 0.f; 

	TArray<TWeakObjectPtr<class UMS_CustomerAIUnit>> CustomerAIUnits;
	TArray<TWeakObjectPtr<class AMS_CustomerSpawnPoint>> CustomerSpawnPoints;
};
