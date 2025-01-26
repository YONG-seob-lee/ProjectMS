// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_MonthFinancialElementWidget.h"

#include "MS_Define.h"
#include "Components/TextBlock.h"
#include "ElementData/MS_MonthFinancialElementData.h"

namespace ElementString
{
	const FString Month = TEXT("{0} < 월 >");
	const FString Gold = TEXT("{0} Gold");
	const FString Count = TEXT("{0} 개");
	const FString Percent = TEXT("{0} %");
}

void UMS_MonthFinancialElementWidget::NativeOnListItemObjectSet(UObject* aListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(aListItemObject);

	const TObjectPtr<UMS_MonthFinancialElementData> Data = Cast<UMS_MonthFinancialElementData>(aListItemObject);
	if(!Data)
	{
		MS_ERROR(TEXT("Warning!! UMS_MonthFinancialElementWidget::NativeOnListItemObjectSet"));
		return;
	}

	CPP_Month->SetText(FText::FromString(FString::Format(*ElementString::Month, {Data->GetMonth()})));
	CPP_CostBuildingStorage->SetText(FText::FromString(FString::Format(*ElementString::Gold, {Data->GetCostBuildingStorage()})));
	CPP_MaintenanceCostMart->SetText(FText::FromString(FString::Format(*ElementString::Gold, {Data->GetMaintenanceCostMart()})));
	CPP_LandPurchasesNumber->SetText(FText::FromString(FString::Format(*ElementString::Count, {Data->GetLandPurchasesNumber()})));
	CPP_AverageAmount->SetText(FText::FromString(FString::Format(*ElementString::Gold, {Data->GetAverageAmount()})));
	CPP_ShelfCapacity->SetText(FText::FromString(FString::Format(*ElementString::Percent, {Data->GetShelfCapacity()})));
	CPP_StaffSalary->SetText(FText::FromString(FString::Format(*ElementString::Gold, {Data->GetStaffSalary()})));
	CPP_LoanInterest->SetText(FText::FromString(FString::Format(*ElementString::Gold, {Data->GetLoanInterest()})));
}

void UMS_MonthFinancialElementWidget::SetIndicatorString() const
{
	CPP_Month->SetText(FText::FromString(TEXT("월 : ")));
	CPP_CostBuildingStorage->SetText(FText::FromString(TEXT("매대 건설비 : ")));
	CPP_MaintenanceCostMart->SetText(FText::FromString(TEXT("마트 유지비 : ")));
	CPP_LandPurchasesNumber->SetText(FText::FromString(TEXT("땅 구입 횟수 : ")));
	CPP_AverageAmount->SetText(FText::FromString(TEXT("물건 평균 금액 : ")));
	CPP_ShelfCapacity->SetText(FText::FromString(TEXT("창고 용적량 : ")));
	CPP_StaffSalary->SetText(FText::FromString(TEXT("직원 급여 : ")));
	CPP_LoanInterest->SetText(FText::FromString(TEXT("대출 이자 : ")));
}
