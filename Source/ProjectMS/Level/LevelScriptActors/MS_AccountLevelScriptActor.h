﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_LevelScriptActorBase.h"
#include "MS_AccountLevelScriptActor.generated.h"

UCLASS()
class PROJECTMS_API AMS_AccountLevelScriptActor : public AMS_LevelScriptActorBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMS_AccountLevelScriptActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
