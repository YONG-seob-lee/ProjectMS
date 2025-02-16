// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_SpawnPoint.h"
#include "MS_OutsideDuckSpawnPoint.generated.h"

UCLASS()
class PROJECTMS_API AMS_OutsideDuckSpawnPoint : public AMS_SpawnPoint
{
	GENERATED_BODY()

public:
	AMS_OutsideDuckSpawnPoint(const FObjectInitializer& ObjectInitializer);

	virtual FVector GetSpawnLocation() override;
	virtual FRotator GetSpawnRotation() override;
	
protected:
	
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
