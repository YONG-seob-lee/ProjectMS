// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_StaffAction.h"

bool UMS_StaffAction::HasStaffActionTarget(EMS_StaffActionType aStaffActionType)
{
	switch (aStaffActionType)
	{
	case EMS_StaffActionType::ChangeClothes :
		{
			return true;
		}
	default:
		{
			return false;
		}	
	}
}
