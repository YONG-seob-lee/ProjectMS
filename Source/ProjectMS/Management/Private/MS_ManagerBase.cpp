// Fill out your copyright notice in the Description page of Project Settings.


#include "../MS_ManagerBase.h"

#include "CoreClass/Controller/MS_PlayerController.h"

TWeakObjectPtr<AMS_PlayerController> UMS_ManagerBase::GetController()
{
	if(AMS_PlayerController* PlayerController = Cast<AMS_PlayerController>(GetOuter()))
	{
		return PlayerController;
	}

	return nullptr;
}
