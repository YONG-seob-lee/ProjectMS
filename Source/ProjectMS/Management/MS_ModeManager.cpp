// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ModeManager.h"

#include "MS_WidgetManager.h"

UMS_ModeManager::UMS_ModeManager()
{
	ModeManager = this;
}

void UMS_ModeManager::SetMode(EMS_ModeType aModeType)
{
	switch(aModeType)
	{
	case(EMS_ModeType::Normal):
		{
			break;
		}
	case(EMS_ModeType::Rotate):
		{
			gModeMng.ShowRotateWidget();
			break;
		}
	case(EMS_ModeType::Construct):
		{
			break;
		}
	case(EMS_ModeType::StaffManagement):
		{
			break;
		}
	case(EMS_ModeType::CustomerManagement):
		{
			break;		
		}
	default:
		{
			break;
		}
	}
}

void UMS_ModeManager::ShowRotateWidget()
{
	gWidgetMng.ShowRotateWidget();
}

UMS_ModeManager* UMS_ModeManager::GetInstance()
{
	return ModeManager;
}
