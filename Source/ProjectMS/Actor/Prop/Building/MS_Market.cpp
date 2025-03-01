// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_Market.h"

#include "Character/AICharacter/MS_AICharacter.h"
#include "Component/Actor/MS_InteractionComponent.h"
#include "Components/WidgetComponent.h"
#include "Engine/TriggerBox.h"
#include "Manager_Both/MS_UnitManager.h"
#include "Manager_Client/MS_PlayerCameraManager.h"
#include "Manager_Client/MS_SceneManager.h"
#include "Manager_Client/MS_SequenceManager.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "Widget/MS_Widget.h"


AMS_Market::AMS_Market(const FObjectInitializer& aObjectInitializer)
	: Super(aObjectInitializer)
{
	InteractionComponent = CreateDefaultSubobject<UMS_InteractionComponent>("InteractionComponent");
	if (InteractionComponent)
	{
		InteractionComponent->SetupAttachment(SceneRootComponent);
	}

	AutoDoorTriggerBox = CreateDefaultSubobject<UBoxComponent>("AutoDoorTriggerBox");
	if(AutoDoorTriggerBox)
	{
		AutoDoorTriggerBox->AttachToComponent(SceneRootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		AutoDoorTriggerBox->SetRelativeLocation(FVector(0.f, 560.f, -230.f));
		AutoDoorTriggerBox->SetBoxExtent(FVector(100.f, 100.f, 100.f));
		AutoDoorTriggerBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &AMS_Market::OnAutoDoorTrigger);
		AutoDoorTriggerBox->OnComponentEndOverlap.AddUniqueDynamic(this, &AMS_Market::OnAutoDoorOutTrigger);
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
		gWidgetMng.HideAllWidget(true);
		PlayTutorial();
		return;
	}
	
	InteractionComponent->OnReleasedEvent();
}

void AMS_Market::LaunchEvent()
{
	Super::LaunchEvent();
	
	CREATE_SCENE_COMMAND(Command);
	Command->SetLevelType(EMS_LevelType::MarketLevel);
	// TODO : All : 언로드해야할 스테이지를 판별해야함.
	Command->SetPreviousLevelType(EMS_LevelType::LobbyLevel, GetWorld());
	Command->SetFadeOutTransitionType(EMS_TransitionStyle::GradationOut);
	Command->SetFadeInTransitionType(EMS_TransitionStyle::GradationIn);
	Command->SetFadeAnimationType(EMS_FadeAnimationCurveType::Linear);
	Command->SetLoadingWidgetType(EMS_LoadingWidgetType::Default);
	gSceneMng.OnFadeFinishedEventDelegate.AddWeakLambda(this, [this]
		{
			gUnitMng.DestroyAllUnits();
			gSceneMng.OnFadeFinishedEventDelegate.RemoveAll(this);
		});
	gSceneMng.RequestChangeScene(Command);

	gUnitMng.DestroyAllUnits();
}

void AMS_Market::OnAutoDoorTrigger(UPrimitiveComponent* PrimitiveComponent, AActor* Actor, UPrimitiveComponent* PrimitiveComponent1, int I, bool bArg, const FHitResult& HitResult)
{
	if(TObjectPtr<AMS_AICharacter> DuckAI = Cast<AMS_AICharacter>(Actor))
	{
		gSequenceMng.PlaySequence(EMS_SequenceType::OpenDoorTown, FMS_SequencePlayParameter(false, false, false));
	}
}

void AMS_Market::OnAutoDoorOutTrigger(UPrimitiveComponent* PrimitiveComponent, AActor* Actor, UPrimitiveComponent* PrimitiveComponent1, int I)
{
	if(TObjectPtr<AMS_AICharacter> DuckAI = Cast<AMS_AICharacter>(Actor))
	{
		gSequenceMng.PlaySequence(EMS_SequenceType::CloseDoorTown, FMS_SequencePlayParameter(false, false, false));
	}
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
	
	TutorialSkipWidget->PlayTutorial(Desc, SubDesc, []()
	{
		gWidgetMng.HideAllWidget(false);
	});
}

