// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_PersonalAction.h"

bool UMS_PersonalAction::HasPersonalActionTarget(EMS_PersonalActionType aPersonalActionType)
{
	switch (aPersonalActionType)
	{
	case EMS_PersonalActionType::ChangeClothes :
		{
			return true;
		}
	default:
		{
			return false;
		}	
	}
}
