// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_LevelScriptActorBase.h"
#include "MS_ConstructibleLevelScriptActorBase.generated.h"

UCLASS()
class PROJECTMS_API AMS_ConstructibleLevelScriptActorBase : public AMS_LevelScriptActorBase
{
	GENERATED_BODY()

public:
	AMS_ConstructibleLevelScriptActorBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void ParsingDefaultPropDatas();
};
