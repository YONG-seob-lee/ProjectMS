// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ChatWidget.h"

#include "MS_ChatEntryWidget.h"
#include "LevelScriptActors/MS_MarketLevelScriptActor.h"
#include "Manager_Client/MS_SceneManager.h"
#include "Widget/WidgetComponent/MS_WidgetSwitcher.h"

namespace ChatNumber
{
	constexpr int32 None = 0;
	constexpr int32 Exist = 1;
}

void UMS_ChatWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

void UMS_ChatWidget::SetChat(MS_Handle aUnitHandle, EMS_PopulationNumber aPopulationNumber) const
{
	if(aPopulationNumber == EMS_PopulationNumber::One)
	{
		if(const TObjectPtr<AMS_MarketLevelScriptActor> MarketLevelScriptActor = Cast<AMS_MarketLevelScriptActor>(gSceneMng.GetCurrentLevelScriptActor()))
		{
			TArray<FMS_ChattingParameter> ChattingParameters;
			MarketLevelScriptActor->GetUnitChatting(aUnitHandle, ChattingParameters);
			CPP_ChatWidgetSwitcher->SetActiveWidgetIndex(ChattingParameters.Num() == 0 ? ChatNumber::None : ChatNumber::Exist);
			CPP_ChatEntry->SetChatting(ChattingParameters);
		}
	}
	else if(aPopulationNumber == EMS_PopulationNumber::Many)
	{
		if(const TObjectPtr<AMS_MarketLevelScriptActor> MarketLevelScriptActor = Cast<AMS_MarketLevelScriptActor>(gSceneMng.GetCurrentLevelScriptActor()))
		{
			TArray<FMS_ChattingParameter> ChattingParameters;
			MarketLevelScriptActor->GetAllChattingCollection(ChattingParameters);
			CPP_ChatWidgetSwitcher->SetActiveWidgetIndex(ChattingParameters.Num() == 0 ? ChatNumber::None : ChatNumber::Exist);
			CPP_ChatEntry->SetChatting(ChattingParameters);
		}
	}
}
