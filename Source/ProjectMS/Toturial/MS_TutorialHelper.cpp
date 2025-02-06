// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_TutorialHelper.h"

void UMS_TutorialHelper::Initialize()
{
	FirstEnterCheckContainer.Emplace(EMS_FirstEnterCheckType::Market, false);
	FirstEnterCheckContainer.Emplace(EMS_FirstEnterCheckType::Schedule, false);
}

void UMS_TutorialHelper::Destroyed()
{
}
