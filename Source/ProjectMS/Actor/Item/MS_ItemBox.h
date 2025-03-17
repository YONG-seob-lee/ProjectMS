// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_ActorBase.h"
#include "MS_ItemBox.generated.h"

UCLASS()
class PROJECTMS_API AMS_ItemBox : public AMS_ActorBase
{
	GENERATED_BODY()

public:
	AMS_ItemBox(const FObjectInitializer& aObjectInitializer);

protected:
	virtual void BeginPlay() override;
};
