// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Modal/MS_CustomerManagementWidget.h"
#include "ScriptActorComponent/MS_MarketLevelScriptActorComponent.h"
#include "ScriptActorComponent/MS_UnitPurchaseCollectComponent.h"
#include "Widget/MS_Widget.h"
#include "MS_PurchaseWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_PurchaseWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	void SetPurchase(MS_Handle aUnitHandle, EMS_PopulationNumber aPopulationNumber) const;

private:
	void SetPurchaseOne_Internal(MS_Handle aUnitHandle) const;
	void SetPurchaseMany_Internal() const;
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_WidgetSwitcher> CPP_PurchaseWidgetSwitcher = nullptr;

	// Person Part
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_ComeInMarketText = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_ComeOutMarketText = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_PurchaseItemsList = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_PurchaseItemCount = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_PurchaseItemsGoldAmount = nullptr;

	// People Part

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_ComeInMarketPeoplePerDay = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_TotalBuyItemCount = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_TotalBuyGoldAmount = nullptr;
	
};
