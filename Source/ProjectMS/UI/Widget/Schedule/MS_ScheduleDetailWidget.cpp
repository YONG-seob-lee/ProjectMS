// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ScheduleDetailWidget.h"

#include "MS_FinancialDetailWidget.h"
#include "Components/TextBlock.h"

void UMS_ScheduleDetailWidget::InitWidget(const FName& aTypeName, bool bManaged, bool bAttachToRoot)
{
	Super::InitWidget(aTypeName, bManaged, bAttachToRoot);

	// for test
	if(CPP_FinancialDetailWidget)
	{
		CPP_FinancialDetailWidget->InitDetail(300, 150, 130, 150, 5, 45, 100);
	}
}

void UMS_ScheduleDetailWidget::SetDay(int32 aDay) const
{
	if(CPP_FinancialIndicator)
	{
		CPP_FinancialIndicator->SetText(FText::FromString(FString::Format(TEXT("{0}일 재무 재표"), {aDay})));
	}
}
