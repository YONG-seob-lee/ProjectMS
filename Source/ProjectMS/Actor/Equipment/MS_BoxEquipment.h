// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_Equipment.h"
#include "MS_BoxEquipment.generated.h"

UCLASS()
class PROJECTMS_API AMS_BoxEquipment : public AMS_Equipment
{
	GENERATED_BODY()

public:
	AMS_BoxEquipment(const FObjectInitializer& aObjectInitializer);

protected:
	virtual void BeginPlay() override;

public:
};
