// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_BuyItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_BuyItemWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	static FName GetWidgetName() { return TEXT("BuyItem"); }
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	void OnClickedConfirmButton();
	void OnClickedCancelButton();
	void OnClickedLoadingUnloading(int32 aCount, FString aItemName);
	
	int32 TotalPrice = 0;
	
	TArray<TObjectPtr<class UMS_OrderItemElementData>> OrderItemElementDatas;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_TileView> CPP_ItemTileView = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_TotalPriceText = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_ConfirmButton> CPP_ConfirmButton = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_ConfirmButton> CPP_CancelButton = nullptr;
};
