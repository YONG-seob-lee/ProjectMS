// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ScheduleDetailWidget.h"

#include "MS_FinancialDetailWidget.h"
#include "Button/MS_Button.h"
#include "Components/TextBlock.h"
#include "Manager_Client/MS_WidgetManager.h"

void UMS_ScheduleDetailWidget::InitWidget(const FName& aTypeName, bool bManaged, bool bAttachToRoot)
{
	Super::InitWidget(aTypeName, bManaged, bAttachToRoot);

	// for test
	if(CPP_FinancialDetailWidget)
	{
		CPP_FinancialDetailWidget->InitDetail(300, 150, 130, 150, 5, 45, 100);
	}

	if (CPP_SkipButton)
	{
		CPP_SkipButton->SetVisibility(ESlateVisibility::Visible);
		CPP_SkipButton->GetOnClickedDelegate().AddUObject(this, &UMS_ScheduleDetailWidget::OnClickedBlankButton);
	}
}

void UMS_ScheduleDetailWidget::SetDay(int32 aDay) const
{
	if(CPP_FinancialIndicator)
	{
		CPP_FinancialIndicator->SetText(FText::FromString(FString::Format(TEXT("{0}일 재무 재표"), {aDay})));
	}
}

void UMS_ScheduleDetailWidget::OnClickedBlankButton()
{
	gWidgetMng.DestroyWidget(this);
}
