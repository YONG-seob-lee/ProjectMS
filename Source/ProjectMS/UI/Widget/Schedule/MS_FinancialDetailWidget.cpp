// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_FinancialDetailWidget.h"

#include "Components/TextBlock.h"

void UMS_FinancialDetailWidget::InitDetail(const FMS_SettlementSheet& aDailySheet) const
{
	CPP_DailySales->SetText(FText::FromString(FString::Format(TEXT("매출액 : {0}Gold"), {aDailySheet.SellItemPrice})));
	CPP_OrderFurnitures->SetText(FText::FromString(FString::Format(TEXT("발주 가구 금액 : {0}Gold"), {aDailySheet.OrderFurnitures})));
	CPP_OrderItems->SetText(FText::FromString(FString::Format(TEXT("발주 물건 금액 : {0}Gold"), {aDailySheet.OrderItems})));
	CPP_ElectricityBill->SetText(FText::FromString(FString::Format(TEXT("전기세 : {0}Gold"), {aDailySheet.ElectricityBill})));
	CPP_PersonalExpanses->SetText(FText::FromString(FString::Format(TEXT("지출 알바비 : {0}Gold"), {aDailySheet.PersonalExpanses})));
	CPP_DailyLoanInterest->SetText(FText::FromString(FString::Format(TEXT("대출 : {0}Gold"), {aDailySheet.LoanInterest})));
	CPP_TotalAggregate->SetText(FText::FromString(FString::Format(TEXT("총계 : {0}Gold"), {aDailySheet.TotalAggregate})));
}
