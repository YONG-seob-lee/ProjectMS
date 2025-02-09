// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_Gate.h"


AMS_Gate::AMS_Gate(const FObjectInitializer& aObjectInitializer)
	: Super(aObjectInitializer), GateIndex(INDEX_NONE), LinkedGateIndex(INDEX_NONE)
{
	// Property
	PropType = EMS_PropType::Gate;
}

void AMS_Gate::BeginPlay()
{
	Super::BeginPlay();
}

