// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_Market.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Component/Actor/MS_InteractionComponent.h"
#include "Components/WidgetComponent.h"
#include "Manager_Client/MS_PlayerCameraManager.h"
#include "Manager_Client/MS_SceneManager.h"
#include "Manager_Client/MS_SequenceManager.h"
#include "Widget/MS_Widget.h"


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
	if(CheckTutorialFinished() == false)
	{
		PlayTutorial();
		return;
	}
	
	InteractionComponent->OnReleasedEvent();
}

void AMS_Market::LaunchEvent()
{
	Super::LaunchEvent();
	
	gCameraMng.LocateCamera(FVector(370.f, 440.f, 0.f), EMS_ViewCameraType::QuarterView);
	gCameraMng.LocateCamera(FVector::ZeroVector, EMS_ViewCameraType::SideView);
	
	CREATE_SCENE_COMMAND(Command);
	Command->SetLevelType(EMS_LevelType::MarketLevel);
	// TODO : All : 언로드해야할 스테이지를 판별해야함.
	Command->SetPreviousLevelType(EMS_LevelType::LobbyLevel);
	Command->SetFadeOutTransitionType(EMS_TransitionStyle::GradationOut);
	Command->SetFadeInTransitionType(EMS_TransitionStyle::GradationIn);
	Command->SetFadeAnimationType(EMS_FadeAnimationCurveType::Linear);
	Command->SetLoadingWidgetType(EMS_LoadingWidgetType::Default);
	Command->OnFadeInFinishedCallback = []()
	{
		gSequenceMng.PlaySequence();
	};

	gSceneMng.RequestChangeScene(Command);
}

bool AMS_Market::CheckTutorialFinished()
{
	const TObjectPtr<UMS_GameUserSettings> GameUserSettings = Cast<UMS_GameUserSettings>(GEngine->GetGameUserSettings());
	if(!GameUserSettings)
	{
		return false;
	}
	
	return GameUserSettings->IsTutorialFinished(EMS_TutorialType::Market);
}

void AMS_Market::PlayTutorial() const
{
	TArray<UActorComponent*> MarketComponents;
	GetComponents(MarketComponents);

	TObjectPtr<UWidgetComponent> TutorialWidgetComponent = nullptr;
	for(const auto& MarketComponent : MarketComponents)
	{
		if(MarketComponent->GetName() == TEXT("TutorialWidgetComponent"))
		{
			TutorialWidgetComponent = Cast<UWidgetComponent>(MarketComponent);
			break;
		}
	}
	
	if(!TutorialWidgetComponent)
	{
		MS_ENSURE(false);
		return;
	}
	const TObjectPtr<UMS_Widget> TutorialSkipWidget = Cast<UMS_Widget>(TutorialWidgetComponent->GetWidget());
	if(!TutorialSkipWidget)
	{
		return;
	}
	
	const TObjectPtr<UMS_TutorialCacheTable> TutorialTable = Cast<UMS_TutorialCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::Tutorial));
	if(TutorialTable == nullptr)
	{
		MS_ENSURE(false);
		return;
	}

	FText Desc = FText();
	FText SubDesc = FText();
	TutorialTable->GetTutorialDesc(static_cast<int32>(EMS_TutorialType::Market), Desc, SubDesc);

	FVector2D ViewPortSize = FVector2D::ZeroVector;
	GetWorld()->GetGameViewport()->GetViewportSize(ViewPortSize);
	FVector2D MousePosition = FVector2D::ZeroVector;
	GetWorld()->GetGameViewport()->GetMousePosition(MousePosition);
	
	if(MousePosition.Y * 2 > ViewPortSize.Y)
	{
		if(MousePosition.X * 2 > ViewPortSize.X)
		{
			//Up
			TutorialSkipWidget->SetTutorialDirection(EMS_TutorialDirection::UpToLeft);	
		}
		else
		{
			TutorialSkipWidget->SetTutorialDirection(EMS_TutorialDirection::UpToRight);
		}
	}
	else
	{
		if(MousePosition.X * 2 > ViewPortSize.X)
		{
			//Down
			TutorialSkipWidget->SetTutorialDirection(EMS_TutorialDirection::DownToLeft);	
		}
		else
		{
			TutorialSkipWidget->SetTutorialDirection(EMS_TutorialDirection::DownToRight);
		}
	}
	
	TutorialSkipWidget->PlayTutorial(Desc, SubDesc);
}

