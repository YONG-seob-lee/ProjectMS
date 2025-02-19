// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_BuyItemWidget.h"

#include "Button/MS_ConfirmButton.h"
#include "Components/TextBlock.h"
#include "Manager_Both/MS_TableManager.h"
#include "Manager_Client/MS_ScheduleManager.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "Table/Caches/MS_ItemCacheTable.h"
#include "Widget/ListViewElement/ElementData/MS_OrderItemElementData.h"
#include "Widget/WidgetComponent/MS_TileView.h"

void UMS_BuyItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	const TObjectPtr<UMS_ItemCacheTable> ItemTable = Cast<UMS_ItemCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::ItemData));
	MS_ENSURE(ItemTable);

	ItemTable->GetOrderItemElementDatas(OrderItemElementDatas);

	if(CPP_ItemTileView)
	{
		CPP_ItemTileView->SetElements(TArray<UObject*>(OrderItemElementDatas));
		for(const auto& OrderItemElementData : OrderItemElementDatas)
		{
			OrderItemElementData->OnClickCountDelegate.AddUObject(this, &UMS_BuyItemWidget::OnClickedLoadingUnloading, OrderItemElementData->GetItemName());
		}
	}

	if(CPP_ConfirmButton)
	{
		CPP_ConfirmButton->SetButtonName(TEXT("구매"));
		CPP_ConfirmButton->GetOnClickedDelegate().AddUObject(this, &UMS_BuyItemWidget::OnClickedConfirmButton);
	}
	if(CPP_CancelButton)
	{
		CPP_CancelButton->SetButtonName(TEXT("취소"));
		CPP_CancelButton->GetOnClickedDelegate().AddUObject(this, &UMS_BuyItemWidget::OnClickedCancelButton);
	}
}

void UMS_BuyItemWidget::NativeDestruct()
{
	for(const auto& OrderItemElementData : OrderItemElementDatas)
	{
		MS_DeleteObject(OrderItemElementData);
	}
	OrderItemElementDatas.Empty();
	
	Super::NativeDestruct();
}

void UMS_BuyItemWidget::OnClickedConfirmButton()
{
	TMap<int32, int32> TransferItems;

	for(const auto& OrderItemElementData : OrderItemElementDatas)
	{
		TransferItems.Emplace(OrderItemElementData->GetItemId(), OrderItemElementData->GetItemCount());
	}
	
	// gScheduleMng.TransferItemsToServer(TransferItems);
	gWidgetMng.CloseModalWidget();
	gWidgetMng.ShowToastMessage(TEXT("물품 구매를 완료했습니다!!"));
}

void UMS_BuyItemWidget::OnClickedCancelButton()
{
	gWidgetMng.CloseModalWidget();
}

void UMS_BuyItemWidget::OnClickedLoadingUnloading(int32 aCount, FString aItemName)
{
	TotalPrice = 0;
	
	for(const auto& OrderItemElementData : OrderItemElementDatas)
	{
		if(OrderItemElementData->GetItemName() == aItemName)
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
