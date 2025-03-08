// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_BuyFurnitureWidget.generated.h"

namespace BuyFurnitureWidget
{
	const FName Shake = TEXT("Shake");
}
/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_BuyFurnitureWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	static FName GetWidgetName() { return TEXT("BuyFurniture"); }
	virtual void InitWidget(const FName& aTypeName, bool bManaged, bool bAttachToRoot) override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	bool bOrder = false;
	
	void InitializeBuyFurnitureWidget();
	
	void OnClickedConfirmButton();
	void OnClickedCancelButton();
	void OnClickedLoadingUnloading(int32 aCount, FString aFurnitureName);

	int32 TotalPrice = 0;
	
	TArray<TObjectPtr<class UMS_OrderItemElementData>> OrderFurnitureElementDatas;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_TileView> CPP_FurnitureTileView = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_TotalPriceText = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_ConfirmButton> CPP_ConfirmButton = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_ConfirmButton> CPP_CancelButton = nullptr;
};
