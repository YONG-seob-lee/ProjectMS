// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Prop/Furniture/MS_Furniture.h"
#include "MS_Wardrobe.generated.h"

UCLASS()
class PROJECTMS_API AMS_Wardrobe : public AMS_Furniture
{
	GENERATED_BODY()

public:
	AMS_Wardrobe(const FObjectInitializer& aObjectInitializer);

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
