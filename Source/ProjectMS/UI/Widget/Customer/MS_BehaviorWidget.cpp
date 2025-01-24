// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_BehaviorWidget.h"

#include "MS_BehaviorEntryWidget.h"
#include "LevelScriptActors/MS_MarketLevelScriptActor.h"
#include "Manager_Client/MS_SceneManager.h"
#include "Widget/WidgetComponent/MS_WidgetSwitcher.h"

namespace BehaviorNumber
{
	constexpr int32 None = 0;
	constexpr int32 Exist = 1;
}

void UMS_BehaviorWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMS_BehaviorWidget::SetBehavior(MS_Handle aUnitHandle, EMS_PopulationNumber aPopulationNumber) const
{
	if(aPopulationNumber == EMS_PopulationNumber::One)
	{
		if(const TObjectPtr<AMS_MarketLevelScriptActor> MarketLevelScriptActor = Cast<AMS_MarketLevelScriptActor>(gSceneMng.GetCurrentLevelScriptActor()))
		{
			TArray<FMS_BehaviorParameter> BehaviorParameters;
			MarketLevelScriptActor->GetUnitBehavior(aUnitHandle, BehaviorParameters);
			CPP_BehaviorWidgetSwitcher->SetActiveWidgetIndex(BehaviorParameters.Num() == 0 ? BehaviorNumber::None : BehaviorNumber::Exist);
			CPP_BehaviorEntry->SetChatting(BehaviorParameters);
		}
	}
	else if(aPopulationNumber == EMS_PopulationNumber::Many)
	{
		if(const TObjectPtr<AMS_MarketLevelScriptActor> MarketLevelScriptActor = Cast<AMS_MarketLevelScriptActor>(gSceneMng.GetCurrentLevelScriptActor()))
		{
			TArray<FMS_BehaviorParameter> BehaviorParameters;
			MarketLevelScriptActor->GetAllBehaviorCollection(BehaviorParameters);
			CPP_BehaviorWidgetSwitcher->SetActiveWidgetIndex(BehaviorParameters.Num() == 0 ? BehaviorNumber::None : BehaviorNumber::Exist);
			CPP_BehaviorEntry->SetChatting(BehaviorParameters);
		}
	}
}
