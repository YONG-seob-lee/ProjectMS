// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/LevelScriptActors/MS_PersistentLevelScriptActor.h"

#include "MS_Define.h"
#include "Controller/MS_PlayerController.h"
#include "MS_SceneManager.h"
#include "MS_WidgetManager.h"
#include "Widget/Persistent/MS_PersistentWidget.h"

// Sets default values
AMS_PersistentLevelScriptActor::AMS_PersistentLevelScriptActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMS_PersistentLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();
	
	gWidgetMng.Create_Widget(UMS_PersistentWidget::GetWidgetName());
	
	CREATE_SCENE_COMMAND(Command);
	Command->SetLevelType(EMS_LevelType::AccountLevel);
	Command->SetPreviousLevelType(EMS_LevelType::PersistenceLevel);
	Command->SetFadeOutTransitionType(EMS_TransitionStyle::Undefined);
	Command->SetFadeInTransitionType(EMS_TransitionStyle::Undefined);
	Command->SetLoadingWidgetType(EMS_LoadingWidgetType::Default);

	gSceneMng.RequestChangeScene(Command);
}

// Called every frame
void AMS_PersistentLevelScriptActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

