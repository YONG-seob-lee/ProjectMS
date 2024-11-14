// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_Management.h"

#include "MS_TableManager.h"
#include "ProjectMS/Utility/MS_Define.h"

void UMS_Management::Initialize()
{
}

void UMS_Management::Finalize()
{
}

void UMS_Management::PostInitialize()
{
}

void UMS_Management::Tick(float aDeltaTime)
{
}

void UMS_Management::InitManager()
{
	// [Create Manager Instance]	MS_NewObject...
	
	TableManager = MS_NewObject<UMS_TableManager>(this);
	MS_CHECK(TableManager);
}
