// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_MarketStartModal.h"

#include "MS_ConstructibleLevelScriptActorBase.h"
#include "Button/MS_Button.h"
#include "Character/AICharacter/StaffAICharacter/MS_StaffAICharacter.h"
#include "LevelScriptActors/MS_MarketLevelScriptActor.h"
#include "Manager_Client/MS_ModeManager.h"
#include "Manager_Client/MS_SceneManager.h"
#include "Manager_Client/MS_ScheduleManager.h"
#include "Manager_Client/MS_SequenceManager.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "Mode/ModeState/MS_ModeState_RunMarketBase.h"
#include "ContentsUtilities/MS_LevelDefine.h"
#include "Mode/ModeState/MS_ModeState_RunMarket.h"

void UMS_MarketStartModal::NativeConstruct()
{
	Super::NativeConstruct();

	CPP_OpeningPlayButton->GetOnClickedDelegate().AddUObject(this, &UMS_MarketStartModal::OnClickedOpeningPlayButton);

	CPP_FastButton->GetOnClickedDelegate().AddWeakLambda(this, [this]()
	{
		gModeMng.ChangeState(EMS_ModeState::RunMarket);
		gWidgetMng.CloseModalWidget();
	});

	
}

void UMS_MarketStartModal::OnClickedOpeningPlayButton()
{
	CPP_OpeningPlayButton->GetOnClickedDelegate().RemoveAll(this);

	gModeMng.ChangeState(EMS_ModeState::RunMarket);
	gWidgetMng.CloseModalWidget([]()
	{
		FMS_SequencePlayParameter Parameter;
		Parameter.OnFinishedSequenceCallback = []()
		{
			if(const UMS_ModeState_RunMarket* RunMarketMode = Cast<UMS_ModeState_RunMarket>(gModeMng.GetCurrentModeState()))
			{
				TMap<int32, int32> ScheduleEvent = {};
				RunMarketMode->GetScheduleEvent(ScheduleEvent);
				gScheduleMng.RunSchedule(ScheduleDefault::GamePlayMinute, ScheduleEvent);

				if (AMS_MarketLevelScriptActor* LevelScriptActor = Cast<AMS_MarketLevelScriptActor>(gSceneMng.GetCurrentLevelScriptActor()))
				{
					TWeakObjectPtr<AActor> UglyDuck = LevelScriptActor->GetLevelSpecificActor(LevelSpecificActorName::UglyDuck);

					if (AMS_StaffAICharacter* StaffUglyDuck = Cast<AMS_StaffAICharacter>(UglyDuck))
					{
						// Animation Mode
						if (USkeletalMeshComponent* SkeletalMesh = StaffUglyDuck->GetMesh())
						{
							SkeletalMesh->SetAnimationMode(EAnimationMode::Type::AnimationBlueprint);
						}

						// Register
						RunMarketMode->RegisterLevelSpecificActorToSupervisor(LevelSpecificActorName::UglyDuck, UglyDuck);
					}
				}
			}
		};
		gSequenceMng.PlaySequence(EMS_SequenceType::Entrance, Parameter);
	});
}
