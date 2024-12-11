// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_ConstructibleLevelScriptActorBase.h"
#include "Environment/MS_LevelPropDatas.h"
#include "MS_ConstructibleLevelScriptActorBase_Indoor.generated.h"

UCLASS()
class PROJECTMS_API AMS_ConstructibleLevelScriptActorBase_Indoor : public AMS_ConstructibleLevelScriptActorBase
{
	GENERATED_BODY()

public:
	AMS_ConstructibleLevelScriptActorBase_Indoor();

	virtual void PostInitializeComponents() override;
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;


protected:
	virtual void ParsingDefaultPropDatas() override;
	
private:
	UPROPERTY()
	FMS_LevelPropDatas_Indoor LevelPropDatas_Indoor;
};
