// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_BuyFurnitureWidget.h"

#include "MS_Define.h"
#include "Button/MS_ConfirmButton.h"
#include "Components/TextBlock.h"
#include "Controller/MS_PlayerController.h"
#include "Manager_Client/MS_ItemManager.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "PlayerState/MS_PlayerState.h"
#include "Table/Caches/MS_FurnitureCacheTable.h"
#include "Widget/ListViewElement/ElementData/MS_OrderItemElementData.h"
#include "Widget/WidgetComponent/MS_TileView.h"

void UMS_BuyFurnitureWidget::InitWidget(const FName& aTypeName, bool bManaged, bool bAttachToRoot)
{
	Super::InitWidget(aTypeName, bManaged, bAttachToRoot);
}

void UMS_BuyFurnitureWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	InitializeBuyFurnitureWidget();
}

void UMS_BuyFurnitureWidget::NativeDestruct()
{
	OrderFurnitureElementDatas.Empty();
	
	Super::NativeDestruct();
}

void UMS_BuyFurnitureWidget::InitializeBuyFurnitureWidget()
{
	OrderFurnitureElementDatas.Empty();
	
	const TObjectPtr<UMS_FurnitureCacheTable> ItemTable = Cast<UMS_FurnitureCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::Furniture));
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
		CPP_ConfirmButton->GetOnClickedDelegate().RemoveAll(this);
		CPP_ConfirmButton->GetOnClickedDelegate().AddUObject(this, &UMS_BuyFurnitureWidget::OnClickedConfirmButton);
	}
	if(CPP_CancelButton)
	{
		CPP_CancelButton->SetButtonName(TEXT("취소"));
		if(CPP_CancelButton->GetOnClickedDelegate().IsBound() == false)
		{
			CPP_CancelButton->GetOnClickedDelegate().AddUObject(this, &UMS_BuyFurnitureWidget::OnClickedCancelButton);
		}
	}
}

void UMS_BuyFurnitureWidget::OnClickedConfirmButton()
{
	if(bOrder)
	{
		return;
	}
	
	TMap<int32, int32> OrderFurnitures;

	for(const auto& OrderItemElementData : OrderFurnitureElementDatas)
	{
		if(OrderItemElementData->GetItemCount() == 0)
		{
			continue;
		}
		OrderFurnitures.Emplace(OrderItemElementData->GetItemId(), OrderItemElementData->GetItemCount());
	}

	if (OrderFurnitures.Num() == 0)
	{
		PlayAnimationByName(BuyFurnitureWidget::Shake);
		gWidgetMng.ShowToastMessage(TEXT("물건을 하나이상 구매하세요"));
		return;	
	}
	// 금액 체크
	if(gItemMng.IsHaveEnoughMoney(OrderFurnitures, true) == false)
	{
		PlayAnimationByName(BuyFurnitureWidget::Shake);
		gWidgetMng.ShowToastMessage(TEXT("금액이 충분하지 않습니다."));
		return;
	}
	

	const TObjectPtr<UWorld> World = GetWorld();
	MS_CHECK(World);

	const TObjectPtr<AMS_PlayerController> PlayerController = World->GetFirstPlayerController<AMS_PlayerController>();
	MS_CHECK(PlayerController);
	
	AMS_PlayerState* PlayerState = PlayerController->GetPlayerState<AMS_PlayerState>();
	MS_CHECK(PlayerState);

  	PlayerState->OrderFurniture(OrderFurnitures);
	
	gWidgetMng.CloseModalWidget();
	gWidgetMng.ShowToastMessage(TEXT("가구 구매를 완료했습니다!!"));
	bOrder = true;
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
