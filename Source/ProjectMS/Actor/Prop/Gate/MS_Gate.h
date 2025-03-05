// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Prop/MS_Prop.h"
#include "MS_Gate.generated.h"

UCLASS()
class PROJECTMS_API AMS_Gate : public AMS_Prop
{
	GENERATED_BODY()

public:
	AMS_Gate(const FObjectInitializer& aObjectInitializer);

protected:
	virtual void BeginPlay() override;


public:
	// Getter
	EMS_ZoneType GetGateZoneType() const;
	EMS_ZoneType GetLinkedZoneType() const;

	TWeakObjectPtr<AMS_Gate> GetLinkedGate() const { return LinkedGate; }

	
private:
	UFUNCTION()
	void OnAutoDoorTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnAutoDoorOutTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	
	// Gate Data
	UPROPERTY(EditInstanceOnly, Category=MS_GateInfo)
	TWeakObjectPtr<AMS_Gate> LinkedGate;
	
	UPROPERTY(EditAnywhere, Category=MS_Gate)
	TObjectPtr<class UBoxComponent> AutoDoorTriggerBox = nullptr;

private:
	UPROPERTY()
	TArray<bool> bOpenedArray = {};
};
