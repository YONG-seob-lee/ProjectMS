// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_MarketStockModalWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_MarketStockModalWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	static FSoftObjectPath GetWidgetPath() { return FSoftObjectPath(TEXT("/Game/UI/Widget/Market/Modal/MarketStockModalWidget.MarketStockModalWidget")); }
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	void CreateStockElement(TMap<int32, int32> aItems, TArray<class UMS_StockItemElementData*>& aStockItemElementData);
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_TileView> CPP_ItemTileView = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_WidgetSwitcher> CPP_ItemSwitcher = nullptr;
	
};
