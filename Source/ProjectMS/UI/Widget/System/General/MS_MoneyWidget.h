// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_MoneyWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_MoneyWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

private:
	void UpdateGold(bool bShowAnimation);
	void UpdateGoldCount();

	int32 CurrentMoney = 0;
	int32 NextMoney = 0;
	FTimerHandle UpdateGoldHandle;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_GoldCount = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UImage> CPP_Coin = nullptr;
	
	UPROPERTY(Meta = (BindWidgetAnim), Transient)
	TObjectPtr<class UWidgetAnimation> UpdateMoney = nullptr;
};
