// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ManagementBoth.h"

#include "MS_Define.h"
#include "Manager_Both/MS_UnitManager.h"

void UMS_ManagementBoth::Initialize()
{
	Super::Initialize();
	
	TableManager = MS_NewObject<UMS_TableManager>(this);
	MS_CHECK(TableManager);
	TableManager->Initialize();
	
	UnitManager = MS_NewObject<UMS_UnitManager>(this);
	MS_CHECK(UnitManager);
	UnitManager->Initialize();
}

void UMS_ManagementBoth::Finalize()
{
	if(TableManager)
	{
		TableManager->Finalize();
		TableManager = nullptr;
	}

	if(UnitManager)
	{
		UnitManager->Finalize();
		UnitManager = nullptr;
	}
	
	Super::Finalize();
}

void UMS_ManagementBoth::BeginPlay()
{
	Super::BeginPlay();
}
