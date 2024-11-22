// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_DefaultButton.h"

#include "MS_Define.h"
#include "Controller/MS_PlayerController.h"
#include "Public/MS_SceneManager.h"

void UMS_DefaultButton::NativeConstruct()
{
	Super::NativeConstruct();
	
	GetOnClickedDelegate().AddUObject(this, &UMS_DefaultButton::OnClickDefaultButton);
}

void UMS_DefaultButton::OnClickDefaultButton()
{
	const TObjectPtr<UWorld> World = GetWorld();
	MS_CHECK(World);
	const TObjectPtr<AMS_PlayerController> PlayerController = Cast<AMS_PlayerController>(World->GetFirstPlayerController());
	MS_CHECK(PlayerController);

	const TObjectPtr<AMS_SceneManager> SceneManager = PlayerController->GetSceneManager();
	MS_CHECK(SceneManager);
	
	CREATE_SCENE_COMMAND(Command);
	Command->SetLevelType(EMS_LevelType::Practice_02);
	Command->SetPreviousLevelType(EMS_LevelType::Practice_01);
	Command->SetFadeInTransitionType(EMS_TransitionStyle::FadeFromLeavingPage);
	Command->SetFadeOutTransitionType(EMS_TransitionStyle::FadeFromEnteringPage);
	Command->SetLoadingWidgetType(EMS_LoadingWidgetType::Default);
	
	SceneManager->RequestChangeScene(Command);
}
