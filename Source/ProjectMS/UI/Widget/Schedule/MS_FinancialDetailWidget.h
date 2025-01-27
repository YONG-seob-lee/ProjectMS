// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_FinancialDetailWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_FinancialDetailWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	void InitDetail(int32 aDailySales, int32 aPurchaseNum, int32 aCostNum
		, int32 aMaintenanceCost, int32 aWorkStaffNum, int32 aEnteredCustomerNum
		, int32 aDailyLoanInterest) const;
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_DailySales = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_ItemPurchaseNum = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_ItemCostNum = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_MartMaintenanceCost = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_WorkStaffNum = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_EnteredCustomerNum = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_DailyLoanInterest = nullptr;
};
