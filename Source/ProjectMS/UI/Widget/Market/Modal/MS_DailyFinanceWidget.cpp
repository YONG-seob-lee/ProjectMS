// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_DailyFinanceWidget.h"

#include "MS_Define.h"
#include "Components/TextBlock.h"
#include "Manager_Client/MS_ScheduleManager.h"

void UMS_DailyFinanceWidget::NativeConstruct()
{
	Super::NativeConstruct();

	const FMS_SettlementSheet& Sheet = gScheduleMng.GetDailySheet();
	if(Sheet.Date == FMS_GameDate())
	{
		MS_ENSURE(false);
		return;
	}

	CPP_DailySale->SetText(FText::FromString(FString::Format(TEXT("+{0} 당일 판매금"), {Sheet.SellItemPrice})));
	CPP_OrderFurniture->SetText(FText::FromString(FString::Format(TEXT("-{0} 매대 구매"), {Sheet.OrderFurnitures})));
	CPP_OrderItem->SetText(FText::FromString(FString::Format(TEXT("-{0} 물건 구매"), {Sheet.OrderItems})));
	CPP_ElectricityBill->SetText(FText::FromString(FString::Format(TEXT("-{0} 전기세"), {Sheet.ElectricityBill})));
	CPP_PersonalExpanses->SetText(FText::FromString(FString::Format(TEXT("-{0} 알바비"), {Sheet.PersonalExpanses})));
	CPP_LoanInterest->SetText(FText::FromString(FString::Format(TEXT("-{0} 이자"), {Sheet.LoanInterest})));
	CPP_TotalAggregate->SetText(FText::FromString(FString::Format(TEXT("총계 : {0}"), {Sheet.TotalAggregate})));
}
