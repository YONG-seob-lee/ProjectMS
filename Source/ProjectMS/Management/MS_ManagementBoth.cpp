// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ManagementBoth.h"

#include "MS_Define.h"
#include "Manager_Both/MS_ModeManager.h"
#include "Manager_Both/MS_SceneManager.h"
#include "Manager_Both/MS_UnitManager.h"

void UMS_ManagementBoth::Initialize()
{
	Super::Initialize();
	
	TableManager = MS_NewObject<UMS_TableManager>(this);
	MS_CHECK(TableManager);
	TableManager->Initialize();

	SceneManager = MS_NewObject<UMS_SceneManager>(this);
	MS_CHECK(SceneManager);
	SceneManager->Initialize();
	
	UnitManager = MS_NewObject<UMS_UnitManager>(this);
	MS_CHECK(UnitManager);
	UnitManager->Initialize();
	
	ModeManager = MS_NewObject<UMS_ModeManager>(this);
	MS_CHECK(ModeManager);
	ModeManager->Initialize();
}