// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/LevelScriptActors/MS_PersistentLevelScriptActor.h"

#include "MS_Define.h"
#include "Manager_Client/MS_SceneManager.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "Widget/Persistent/MS_PersistentWidget.h"


AMS_PersistentLevelScriptActor::AMS_PersistentLevelScriptActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMS_PersistentLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();

	gWidgetMng.CreateRoot();
	gSceneMng.InitRootWidget();
	gWidgetMng.Create_Widget(UMS_PersistentWidget::GetWidgetName());
	
	CREATE_SCENE_COMMAND(Command);
	Command->SetLevelType(EMS_LevelType::AccountLevel);
	Command->SetPreviousLevelType(EMS_LevelType::PersistenceLevel);
	Command->SetFadeOutTransitionType(EMS_TransitionStyle::Undefined);
	Command->SetFadeInTransitionType(EMS_TransitionStyle::Undefined);
	Command->SetLoadingWidgetType(EMS_LoadingWidgetType::Default);

	gSceneMng.RequestChangeScene(Command);
}

void AMS_PersistentLevelScriptActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

