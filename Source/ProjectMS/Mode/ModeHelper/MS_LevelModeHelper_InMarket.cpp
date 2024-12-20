// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_LevelModeHelper_InMarket.h"

#include "Manager_Client/MS_ModeManager.h"
#include "Mode/ModeState/MS_ModeState_Construct.h"
#include "Mode/ModeState/MS_ModeState_Normal.h"


UMS_LevelModeHelper_InMarket::UMS_LevelModeHelper_InMarket()
{
}


void UMS_LevelModeHelper_InMarket::RegisterMode()
{
	Super::RegisterMode();

	gModeMng.RegisterModeState(EMS_ModeState::Normal, FName("Normal"), UMS_ModeState_Normal::StaticClass());
	gModeMng.RegisterModeState(EMS_ModeState::Construct, FName("Construct"), UMS_ModeState_Construct::StaticClass());
}

void UMS_LevelModeHelper_InMarket::UnregisterMode()
{
	Super::UnregisterMode();
}

void UMS_LevelModeHelper_InMarket::BeginDefaultMode()
{
	Super::BeginDefaultMode();

	gModeMng.ChangeState(EMS_ModeState::Normal);
}
