// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_GameState.h"

#include "MS_Define.h"
#include "MS_ManagementBoth.h"

void AMS_GameState::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	RegisterManagement();
}

void AMS_GameState::BeginPlay()
{
	Super::BeginPlay();
}

void AMS_GameState::RegisterManagement()
{
	if (ManagementBoth)
	{
		return;
	}
	
	ManagementBoth = MS_NewObject<UMS_ManagementBoth>(this);
	ManagementBoth->Initialize();
}
