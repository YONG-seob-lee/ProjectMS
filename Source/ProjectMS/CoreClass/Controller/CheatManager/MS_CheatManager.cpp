// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_CheatManager.h"

#include "Manager_Both/MS_UnitManager.h"
#include "Manager_Client/MS_ScheduleManager.h"
#include "Manager_Client/MS_WidgetManager.h"

void UMS_CheatManager::TestCheatManager(const FString aTestString)
{
	gWidgetMng.ShowMessageOnScreen(aTestString);
}

void UMS_CheatManager::AIChatting(int32 UnitId, const FString& Chatting)
{
	gUnitMng.OnChattingDelegate.Broadcast(FMS_ChattingParameter(UnitId, gScheduleMng.GetCurrentMinute(), FText::FromString(Chatting)));
}
