// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ChatWidget.h"

#include "MS_ChatEntryWidget.h"
#include "LevelScriptActors/MS_MarketLevelScriptActor.h"

void UMS_ChatWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

void UMS_ChatWidget::SetChat(MS_Handle aUnitHandle, EMS_PopulationNumber aPopulationNumber) const
{
	if(aPopulationNumber == EMS_PopulationNumber::One)
	{
		if(const TObjectPtr<AMS_MarketLevelScriptActor> MarketLevelScriptActor = Cast<AMS_MarketLevelScriptActor>(GetWorld()->GetLevelScriptActor()))
		{
			TArray<FMS_ChattingParameter> ChattingParameters;
			MarketLevelScriptActor->GetUnitChatting(aUnitHandle, ChattingParameters);
			CPP_ChatEntry->SetChatting(ChattingParameters);
		}
	}
}
