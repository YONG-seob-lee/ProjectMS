// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_MoneyWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Manager_Client/MS_ItemManager.h"

void UMS_MoneyWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	gItemMng.OnUpdateEarnMoneyDelegate.AddUObject(this, &UMS_MoneyWidget::UpdateGold);
	CPP_Coin->SetVisibility(ESlateVisibility::Collapsed);
	
	CurrentMoney = gItemMng.GetTotalGoldMoney();
	NextMoney = 0;
}

void UMS_MoneyWidget::UpdateGold(bool bShowAnimation)
{
	if(CPP_GoldCount)
	{
		NextMoney = gItemMng.GetTotalGoldMoney();
		GetWorld()->GetTimerManager().SetTimer(UpdateGoldHandle, this, &UMS_MoneyWidget::UpdateGoldCount,0.005f, true);
	}

	if(bShowAnimation)
	{
		PlayAnimation(UpdateMoney);
	}
}

void UMS_MoneyWidget::UpdateGoldCount()
{
	if(CurrentMoney >= NextMoney)
	{
		CurrentMoney = NextMoney;
		GetWorld()->GetTimerManager().ClearTimer(UpdateGoldHandle);
	}
	CPP_GoldCount->SetText(FText::FromString(FString::FromInt(++CurrentMoney) + TEXT(" G")));
}
