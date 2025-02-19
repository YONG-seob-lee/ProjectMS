// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_BuyFurnitureWidget.h"

#include "MS_Define.h"
#include "Button/MS_ConfirmButton.h"
#include "Components/TextBlock.h"
#include "Manager_Client/MS_ScheduleManager.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "Table/Caches/MS_StorageCacheTable.h"
#include "Widget/ListViewElement/ElementData/MS_OrderItemElementData.h"
#include "Widget/WidgetComponent/MS_TileView.h"

void UMS_BuyFurnitureWidget::NativeConstruct()
{
	Super::NativeConstruct();

	const TObjectPtr<UMS_StorageCacheTable> ItemTable = Cast<UMS_StorageCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::Storage));
	MS_ENSURE(ItemTable);

	ItemTable->GetOrderFurnitureElementDatas(OrderFurnitureElementDatas);

	if(CPP_FurnitureTileView)
	{
		CPP_FurnitureTileView->SetElements(TArray<UObject*>(OrderFurnitureElementDatas));
		for(const auto& OrderFurnitureElementData : OrderFurnitureElementDatas)
		{
			OrderFurnitureElementData->OnClickCountDelegate.AddUObject(this, &UMS_BuyFurnitureWidget::OnClickedLoadingUnloading, OrderFurnitureElementData->GetItemName());
		}
	}

	if(CPP_ConfirmButton)
	{
		CPP_ConfirmButton->SetButtonName(TEXT("구매"));
		CPP_ConfirmButton->GetOnClickedDelegate().AddUObject(this, &UMS_BuyFurnitureWidget::OnClickedConfirmButton);
	}
	if(CPP_CancelButton)
	{
		CPP_CancelButton->SetButtonName(TEXT("취소"));
		CPP_CancelButton->GetOnClickedDelegate().AddUObject(this, &UMS_BuyFurnitureWidget::OnClickedCancelButton);
	}
}

void UMS_BuyFurnitureWidget::NativeDestruct()
{
	// for(const auto& OrderItemElementData : OrderFurnitureElementDatas)
	// {
	// 	MS_DeleteObject(OrderItemElementData);
	// }
	OrderFurnitureElementDatas.Empty();
	
	Super::NativeDestruct();
}

void UMS_BuyFurnitureWidget::OnClickedConfirmButton()
{
	TMap<int32, int32> TransferItems;

	for(const auto& OrderItemElementData : OrderFurnitureElementDatas)
	{
		TransferItems.Emplace(OrderItemElementData->GetItemId(), OrderItemElementData->GetItemCount());
	}
	
	// gScheduleMng.TransferItemsToServer(TransferItems);
	gWidgetMng.CloseModalWidget();
	gWidgetMng.ShowToastMessage(TEXT("가구 구매를 완료했습니다!!"));
}

void UMS_BuyFurnitureWidget::OnClickedCancelButton()
{
	gWidgetMng.CloseModalWidget();
}

void UMS_BuyFurnitureWidget::OnClickedLoadingUnloading(int32 aCount, FString aFurnitureName)
{
	TotalPrice = 0;
	
	for(const auto& OrderItemElementData : OrderFurnitureElementDatas)
	{
		if(OrderItemElementData->GetItemName() == aFurnitureName)
		{
			OrderItemElementData->SetItemCount(aCount);
		}

		TotalPrice += OrderItemElementData->GetItemPrice() * OrderItemElementData->GetItemCount();
	}

	if(CPP_TotalPriceText)
	{
		CPP_TotalPriceText->SetText(FText::FromString(FString::Format(TEXT("합계 : {0}.0 Gold"), { TotalPrice })));
	}
}
