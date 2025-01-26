// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Widget/MS_Widget.h"
#include "MS_MonthFinancialElementWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_MonthFinancialElementWidget : public UMS_Widget, public IUserObjectListEntry
{
	GENERATED_BODY()
public:
	virtual void NativeOnListItemObjectSet(UObject* aListItemObject) override;

	void SetIndicatorString() const;
private:
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_Month = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_CostBuildingStorage = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_MaintenanceCostMart = nullptr;

	UPROPERTY(Meta = (BindWidget))
    TObjectPtr<class UTextBlock> CPP_LandPurchasesNumber = nullptr;
    	
    UPROPERTY(Meta = (BindWidget))
    TObjectPtr<class UTextBlock> CPP_AverageAmount = nullptr;
        	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_ShelfCapacity = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_StaffSalary = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_LoanInterest = nullptr;
};
