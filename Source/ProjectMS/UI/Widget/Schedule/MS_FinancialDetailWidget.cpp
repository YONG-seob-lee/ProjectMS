// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_FinancialDetailWidget.h"

#include "Components/TextBlock.h"

void UMS_FinancialDetailWidget::InitDetail(int32 aDailySales, int32 aPurchaseNum, int32 aCostNum, int32 aMaintenanceCost, int32 aWorkStaffNum, int32 aEnteredCustomerNum, int32 aDailyLoanInterest) const
{
	CPP_DailySales->SetText(FText::FromString(FString::Format(TEXT("매출액 : {0}Gold"), {aDailySales})));
	CPP_ItemPurchaseNum->SetText(FText::FromString(FString::Format(TEXT("구매 물건 갯수 : {0}개"), {aPurchaseNum})));
	CPP_ItemCostNum->SetText(FText::FromString(FString::Format(TEXT("소비 물건 갯수 : {0}개"), {aCostNum})));
	CPP_MartMaintenanceCost->SetText(FText::FromString(FString::Format(TEXT("마켓 유지비 : {0}Gold"), {aMaintenanceCost})));
	CPP_WorkStaffNum->SetText(FText::FromString(FString::Format(TEXT("출근한 직원 수 : {0}명"), {aWorkStaffNum})));
	CPP_EnteredCustomerNum->SetText(FText::FromString(FString::Format(TEXT("입장한 직원 수 : {0}명"), {aEnteredCustomerNum})));
	CPP_DailyLoanInterest->SetText(FText::FromString(FString::Format(TEXT("대출 이자 : {0}Gold"), {aDailyLoanInterest})));
}
