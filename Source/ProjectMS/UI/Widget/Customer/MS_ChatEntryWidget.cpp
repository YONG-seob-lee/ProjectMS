// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ChatEntryWidget.h"

#include "Widget/ListViewElement/ElementData/MS_ChatElementData.h"
#include "Widget/WidgetComponent/MS_ListView.h"

void UMS_ChatEntryWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMS_ChatEntryWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UMS_ChatEntryWidget::SetChatting(TArray<FMS_ChattingParameter>& aChattingParameters) const
{
	TArray<UMS_ChatElementData*> ChatElementDatas;
	UMS_ChatElementData* ChatElementData = MS_NewObject<UMS_ChatElementData>();
	for(const auto& ChattingParameter : aChattingParameters)
	{
		ChatElementData->SetUnitHandle(ChattingParameter.UnitHandle);
		ChatElementData->SetMinute(ChattingParameter.Minute);
		ChatElementData->SetChatting(ChattingParameter.Chatting);
	}
	CPP_ChatListView->SetListItems(ChatElementDatas);
}
