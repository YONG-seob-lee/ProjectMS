// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ManagerBase.h"

TObjectPtr<UMS_ManagerBase> UMS_ManagerBase::GetInstance()
{
	return Manager;
}
