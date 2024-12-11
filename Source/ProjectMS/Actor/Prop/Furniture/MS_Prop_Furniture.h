// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Prop/MS_Prop.h"
#include "MS_Prop_Furniture.generated.h"

UCLASS()
class PROJECTMS_API AMS_Prop_Furniture : public AMS_Prop
{
	GENERATED_BODY()

public:
	AMS_Prop_Furniture();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
