// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_Market.h"

#include "Component/Actor/MS_InteractionComponent.h"
#include "Manager_Client/MS_PlayerCameraManager.h"
#include "Manager_Client/MS_SceneManager.h"


AMS_Market::AMS_Market(const FObjectInitializer& aObjectInitializer)
	: Super(aObjectInitializer)
{
	InteractionComponent = CreateDefaultSubobject<UMS_InteractionComponent>("InteractionComponent");
	if (InteractionComponent)
	{
		InteractionComponent->SetupAttachment(SceneRootComponent);
	}
}

void AMS_Market::BeginPlay()
{
	Super::BeginPlay();
	
}

bool AMS_Market::HasInteractionComponent()
{
	return InteractionComponent != nullptr;
}

void AMS_Market::OnPressDownEvent()
{
	InteractionComponent->OnPressedEvent();
}

void AMS_Market::OnPressUpEvent()
{
	InteractionComponent->OnReleasedEvent();
}

void AMS_Market::LaunchEvent()
{
	Super::LaunchEvent();
	
	gCameraMng.LocateAndRotateCamera(FVector(370.f, 440.f, 0.f), FRotator::ZeroRotator, EMS_ViewCameraType::QuarterView);
	gCameraMng.LocateAndRotateCamera(FVector::ZeroVector, FRotator::ZeroRotator, EMS_ViewCameraType::SideView);
	
	CREATE_SCENE_COMMAND(Command);
	Command->SetLevelType(EMS_LevelType::MarketLevel);
	// TODO : All : 언로드해야할 스테이지를 판별해야함.
	Command->SetPreviousLevelType(EMS_LevelType::Stage01);
	Command->SetFadeOutTransitionType(EMS_TransitionStyle::GradationOut);
	Command->SetFadeInTransitionType(EMS_TransitionStyle::GradationIn);
	Command->SetFadeAnimationType(EMS_FadeAnimationCurveType::Linear);
	Command->SetLoadingWidgetType(EMS_LoadingWidgetType::Default);

	gSceneMng.RequestChangeScene(Command);
}

