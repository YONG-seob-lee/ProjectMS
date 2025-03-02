// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ContentsUtilities/MS_GameProcessDefine.h"
#include "Widget/MS_Widget.h"
#include "MS_DailyFinanceWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_DailyFinanceWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

private:
	FMS_GameDate DailyDate = FMS_GameDate();
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_DailySale = nullptr;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_OrderFurniture = nullptr;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_OrderItem = nullptr;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_ElectricityBill = nullptr;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_PersonalExpanses = nullptr;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_LoanInterest = nullptr;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_TotalAggregate = nullptr;
	
};
