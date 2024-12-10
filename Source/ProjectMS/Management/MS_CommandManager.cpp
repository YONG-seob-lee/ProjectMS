// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_CommandManager.h"

UMS_CommandManager::UMS_CommandManager()
{
	CommandManager = this;
}

void UMS_CommandManager::SetMode(EMS_ModeType aModeType)
{
}

UMS_CommandManager* UMS_CommandManager::GetInstance()
{
	return CommandManager;
}
