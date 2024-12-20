// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_LevelModeHelper.h"

#include "Manager_Client/MS_ModeManager.h"


UMS_LevelModeHelper::UMS_LevelModeHelper()
{
}

void UMS_LevelModeHelper::Initialize()
{
	RegisterMode();

	BeginDefaultMode();
}

void UMS_LevelModeHelper::Finalize()
{
	UnregisterMode();
}

void UMS_LevelModeHelper::RegisterMode()
{
}

void UMS_LevelModeHelper::UnregisterMode()
{
	gModeMng.UnregisterModeStates();;
}

void UMS_LevelModeHelper::BeginDefaultMode()
{
}
