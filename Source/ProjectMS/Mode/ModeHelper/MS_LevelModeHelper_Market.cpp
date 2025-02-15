// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_LevelModeHelper_Market.h"

#include "Manager_Client/MS_ModeManager.h"
#include "Mode/ModeState/MS_ModeState_Construct.h"
#include "Mode/ModeState/MS_ModeState_Normal.h"
#include "Mode/ModeState/MS_ModeState_RunMarketNormal.h"


UMS_LevelModeHelper_Market::UMS_LevelModeHelper_Market()
{
}


void UMS_LevelModeHelper_Market::RegisterMode()
{
	Super::RegisterMode();

	gModeMng.RegisterModeState(EMS_ModeState::Normal, FName("Normal"), UMS_ModeState_Normal::StaticClass());
	gModeMng.RegisterModeState(EMS_ModeState::Construct, FName("Construct"), UMS_ModeState_Construct::StaticClass());
	gModeMng.RegisterModeState(EMS_ModeState::RunMarketNormal, FName("RunMarketNormal"), UMS_ModeState_RunMarketNormal::StaticClass());
}

void UMS_LevelModeHelper_Market::UnregisterMode()
{
	Super::UnregisterMode();
}

void UMS_LevelModeHelper_Market::BeginDefaultMode()
{
	Super::BeginDefaultMode();

	gModeMng.ChangeState(EMS_ModeState::Normal);
}
