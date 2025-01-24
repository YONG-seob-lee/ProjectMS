// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_BehaviorEntryWidget.h"
#include "MS_Define.h"
#include "Widget/ListViewElement/ElementData/MS_BehaviorElementData.h"
#include "Widget/WidgetComponent/MS_ListView.h"

void UMS_BehaviorEntryWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMS_BehaviorEntryWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UMS_BehaviorEntryWidget::SetChatting(TArray<FMS_BehaviorParameter>& aChattingParameters) const
{
	TArray<UMS_BehaviorElementData*> ChatElementDatas;
	for(const auto& ChattingParameter : aChattingParameters)
	{
		UMS_BehaviorElementData* BehaviorElementData = MS_NewObject<UMS_BehaviorElementData>();
		BehaviorElementData->SetUnitHandle(ChattingParameter.UnitHandle);
		BehaviorElementData->SetMinute(ChattingParameter.Minute);
		BehaviorElementData->SetBehavior(ChattingParameter.Behavior);
		ChatElementDatas.Emplace(BehaviorElementData);
	}
	CPP_BehaviorListView->SetListItems(ChatElementDatas);
}
