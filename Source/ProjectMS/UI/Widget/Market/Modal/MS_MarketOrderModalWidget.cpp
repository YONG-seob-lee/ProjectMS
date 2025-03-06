// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_MarketOrderModalWidget.h"

#include "Button/MS_Button.h"
#include "Button/MS_ConfirmButton.h"
#include "Components/TextBlock.h"
#include "Manager_Both/MS_TableManager.h"
#include "Manager_Client/MS_ItemManager.h"
#include "Manager_Client/MS_ScheduleManager.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "PlayerState/MS_PlayerState.h"
#include "Table/Caches/MS_ItemCacheTable.h"
#include "Widget/ListViewElement/ElementData/MS_OrderItemElementData.h"
#include "Widget/WidgetComponent/MS_TileView.h"

void UMS_MarketOrderModalWidget::NativeConstruct()
{
	Super::NativeConstruct();

	const TObjectPtr<UMS_ItemCacheTable> ItemTable = Cast<UMS_ItemCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::ItemData));
	MS_CHECK(ItemTable);

	ItemTable->GetOrderItemElementDatas(OrderItemElementDatas);

	if(CPP_ItemTileView)
	{
		CPP_ItemTileView->SetElements(TArray<UObject*>(OrderItemElementDatas));
		for(const auto& OrderItemElementData : OrderItemElementDatas)
		{
			OrderItemElementData->OnClickCountDelegate.AddUObject(this, &UMS_MarketOrderModalWidget::OnClickedLoadingUnloading, OrderItemElementData->GetItemName());
		}
	}

	if(CPP_ConfirmButton)
	{
		CPP_ConfirmButton->SetButtonName(TEXT("구매"));
		CPP_ConfirmButton->GetOnClickedDelegate().AddUObject(this, &UMS_MarketOrderModalWidget::OnClickedConfirmButton);
	}
	if(CPP_CancelButton)
	{
		CPP_CancelButton->SetButtonName(TEXT("취소"));
		CPP_CancelButton->GetOnClickedDelegate().AddUObject(this, &UMS_MarketOrderModalWidget::OnClickedCancelButton);
	}
}

void UMS_MarketOrderModalWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UMS_MarketOrderModalWidget::OnClickedConfirmButton()
{
	TMap<int32, int32> OrderItems;

	for(const auto& OrderItemElementData : OrderItemElementDatas)
	{
		OrderItems.Emplace(OrderItemElementData->GetItemId(), OrderItemElementData->GetItemCount());
	}

	gItemMng.IsHaveEnoughMoney(OrderItems);

	const TObjectPtr<UWorld> World = GetWorld();
	if(!World)
	{
		return;
	}
	const TObjectPtr<APlayerController> Controller = World->GetFirstPlayerController();
	if(!Controller)
	{
		return;
	}
	const TObjectPtr<AMS_PlayerState> PlayerState = Controller->GetPlayerState<AMS_PlayerState>();
	if(!PlayerState)
	{
		return;
	}
	PlayerState->OrderItem(OrderItems);
	
	gWidgetMng.CloseModalWidget();
	gWidgetMng.ShowToastMessage(TEXT("물품 구매를 완료했습니다!!"));
}

void UMS_MarketOrderModalWidget::OnClickedCancelButton()
{
	gWidgetMng.CloseModalWidget();
}

void UMS_MarketOrderModalWidget::OnClickedLoadingUnloading(int32 aCount, FString aItemName)
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
