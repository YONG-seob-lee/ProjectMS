// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Prop/MS_Prop.h"
#include "MS_Prop_Wall.generated.h"

UCLASS()
class PROJECTMS_API AMS_Prop_Wall : public AMS_Prop
{
	GENERATED_BODY()

public:
	AMS_Prop_Wall();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
