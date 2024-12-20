// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Level/MS_ConstructibleLevelScriptActorBase.h"
#include "MS_InMarketLevelScriptActor.generated.h"

UCLASS()
class PROJECTMS_API AMS_InMarketLevelScriptActor : public AMS_ConstructibleLevelScriptActorBase
{
	GENERATED_BODY()

public:
	AMS_InMarketLevelScriptActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
