// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectMS/Management/MS_Management.h"
#include "ProjectMS/Unit/MS_UnitBase.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "MS_Controller.generated.h"

UCLASS()
class PROJECTMS_API AMS_Controller : public AAIController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMS_Controller();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float aDeltaTime) override;

private:
	UPROPERTY()
	TObjectPtr<UMS_UnitBase> UnitBase = nullptr;

	UPROPERTY()
	TObjectPtr<UMS_Management> Management = nullptr;
};
