// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_FinancialManagementWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_FinancialManagementWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	static FName GetWidgetName() { return TEXT("FinancialManagement"); }
	virtual void InitWidget(const FName& aTypeName, bool bManaged, bool bAttachToRoot) override;

private:
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_MonthFinancialElementWidget> CPP_FinancialIndicator = nullptr;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_ListView> CPP_MonthFinancialListView = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_TotalFinanceWidget> CPP_TotalFinance = nullptr;
};
