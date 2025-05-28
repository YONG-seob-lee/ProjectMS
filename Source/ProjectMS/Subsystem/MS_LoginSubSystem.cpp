// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_LoginSubSystem.h"

#include "Auth/MS_AuthenticationInterface.h"

void UMS_LoginSubSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	SetAuthManager<FMS_GoogleLoginManager>();
}
