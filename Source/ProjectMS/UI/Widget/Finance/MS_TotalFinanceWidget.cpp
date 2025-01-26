// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_TotalFinanceWidget.h"

#include "Components/TextBlock.h"

void UMS_TotalFinanceWidget::SetTotalFinance(int32 aLoan, int32 aInterestRate, int32 aMartValue, int32 aFinance, float aMartGrade) const
{
	CPP_Loans->SetText(FText::FromString(FString::Format(TEXT("[{0} Gold] (금리 : {1} % / 월)"), {aLoan, aInterestRate})));
	CPP_MartValue->SetText(FText::FromString(FString::Format(TEXT("마트 가치 : {0} Gold"), {aMartValue})));
	CPP_Finance->SetText(FText::FromString(FString::Format(TEXT("재정 : {0} Gold"), {aFinance})));
	CPP_MartGrade->SetText(FText::FromString(FString::Format(TEXT("마트 등급 : {0} Star"), {aMartGrade})));
}
