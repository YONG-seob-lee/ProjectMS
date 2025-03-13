// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_LevelScriptActorBase.h"
#include "MS_StageLevelScriptActor.generated.h"

UENUM()
enum class EMS_DayAndNight
{
	Day,
	Night,
};

UCLASS()
class PROJECTMS_API AMS_StageLevelScriptActor : public AMS_LevelScriptActorBase
{
	GENERATED_BODY()

public:
	AMS_StageLevelScriptActor();

	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;

	void SetDayAndNight(EMS_DayAndNight aDayAndNight, bool bDirectly = false);
	
private:
	void SetDayAndNight_Internal(EMS_DayAndNight aDayAndNight, bool bDirectly);
	
	void SetLightColor(EMS_DayAndNight aDayAndNight) const;
	void SetLightProp(EMS_DayAndNight aDayAndNight);
	void SetLightCar(EMS_DayAndNight aDayAndNight);
	
	void CollectOutsideDuckSpawnPoint() const;
	
	void CashingNightPropActors();
	void CashingNightCarActors();
	
	void CashingCarSplineActors() const;
	void CashingDuckSplineActors() const;
	
	
	UFUNCTION()
	void OnPressDownEvent(FVector2D aPointerDownPosition, const FHitResult& aInteractableHitResult);
	
	UFUNCTION()
	void OnPressUpEvent(FVector2D aPointerUpPosition, const FHitResult& aInteractableHitResult);

	void ProcessNightToDay(float DeltaTime);
	
	float DirectionalLightColorVolume = 0.f;
	bool bStartNightToDayTrigger = false;
	
	UPROPERTY()
	TArray<class AMS_NightProp*> NightProps = {};

	UPROPERTY()
	TArray<class AMS_VehicleCharacter*> Cars = {}; 
};
