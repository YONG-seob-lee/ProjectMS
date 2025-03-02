// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager_Client/MS_ScheduleManager.h"
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
	void InitDetail(const FMS_SettlementSheet& aDailySheet) const;
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_DailySales = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_OrderFurnitures = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_OrderItems = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_ElectricityBill = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_PersonalExpanses = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_DailyLoanInterest = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_TotalAggregate = nullptr;
};
