// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ScheduleDetailWidget.h"

#include "MS_FinancialDetailWidget.h"
#include "Button/MS_Button.h"
#include "Components/TextBlock.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "Widget/WidgetComponent/MS_WidgetSwitcher.h"

void UMS_ScheduleDetailWidget::InitWidget(const FName& aTypeName, bool bManaged, bool bAttachToRoot)
{
	Super::InitWidget(aTypeName, bManaged, bAttachToRoot);
	
	if (CPP_SkipButton)
	{
		CPP_SkipButton->SetVisibility(ESlateVisibility::Visible);
		CPP_SkipButton->GetOnClickedDelegate().AddUObject(this, &UMS_ScheduleDetailWidget::OnClickedBlankButton);
	}
}

void UMS_ScheduleDetailWidget::SetDetail(const FMS_SettlementSheet& aDailySheet) const
{
	if(CPP_FinancialIndicator)
	{
		CPP_FinancialIndicator->SetText(FText::FromString(FString::Format(TEXT("{0}일 재무 재표"), {aDailySheet.Date.Day})));
	}

	FMS_SettlementSheet Sheet;
	if(gScheduleMng.GetSettlementSheet(aDailySheet.Date, Sheet) == false)
	{
		CPP_WidgetSwitcher->SetActiveWidgetIndex(0);
	}
	else
	{
		CPP_WidgetSwitcher->SetActiveWidgetIndex(1);
	}
	
	if(CPP_FinancialDetailWidget)
	{
		CPP_FinancialDetailWidget->InitDetail(aDailySheet);
	}
}

void UMS_ScheduleDetailWidget::OnClickedBlankButton()
{
	gWidgetMng.DestroyWidget(this);
}
