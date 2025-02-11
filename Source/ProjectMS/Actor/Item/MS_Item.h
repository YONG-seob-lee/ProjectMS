// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_Actor.h"
#include "MS_Item.generated.h"

UCLASS()
class PROJECTMS_API AMS_Item : public AMS_Actor
{
	GENERATED_BODY()

public:
	AMS_Item(const FObjectInitializer& aObjectInitializer);

protected:
	virtual void BeginPlay() override;
};
