// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ConstructibleLevelScriptActorBase.h"


AMS_ConstructibleLevelScriptActorBase::AMS_ConstructibleLevelScriptActorBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMS_ConstructibleLevelScriptActorBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMS_ConstructibleLevelScriptActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMS_ConstructibleLevelScriptActorBase::ParsingDefaultPropDatas()
{
}
