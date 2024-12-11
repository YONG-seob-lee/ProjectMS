// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ModeManager.h"

UMS_ModeManager::UMS_ModeManager()
{
	ModeManager = this;
}

void UMS_ModeManager::SetMode(EMS_ModeType aModeType)
{
}

UMS_ModeManager* UMS_ModeManager::GetInstance()
{
	return ModeManager;
}
