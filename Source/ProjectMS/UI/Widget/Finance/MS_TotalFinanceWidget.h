// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_TotalFinanceWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_TotalFinanceWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	void SetTotalFinance(int32 aLoan, int32 aInterestRate, int32 aMartValue, int32 aFinance, float aMartGrade) const;
	
private:
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_Loans = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_MartValue = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_Finance = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_MartGrade = nullptr;
};
