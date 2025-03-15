// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ZoneOpenWidget.h"

#include "Button/MS_Button.h"
#include "Components/TextBlock.h"
#include "Manager_Client/MS_ItemManager.h"
#include "Manager_Client/MS_WidgetManager.h"

void UMS_ZoneOpenWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	CPP_ZoneOpenButton->GetOnClickedDelegate().AddUObject(this, &UMS_ZoneOpenWidget::OnClickZoneOpenButton);
}

void UMS_ZoneOpenWidget::SetPrice(int32 _Price)
{
	ZonePrice = _Price;
	CPP_ZonePrice->SetText(FText::FromString(FString::FromInt(_Price)));
}

void UMS_ZoneOpenWidget::OnClickZoneOpenButton()
{
	FMS_SystemParameter SystemParameter;
	SystemParameter.bUseBlurButton = true;
	SystemParameter.bShowExitButton = true;
	SystemParameter.Title = TEXT("\"구역\" 확장");
	
	SystemParameter.Desc = FString::Format(TEXT("구역 확장 공사를 위해 \'{0}\' 금액을 지불하시겠습니까?"), {ZonePrice});
	SystemParameter.Deny = TEXT("금액이 부족합니다!!");
	SystemParameter.InteractButtonType = EMS_InteractButtonType::Both;
	SystemParameter.OnClickedConfirmButtonCallback = [this](bool& bExceptConfirm)
	{
		if(gItemMng.IsHaveEnoughMoney(ZonePrice))
		{
			bExceptConfirm = true;
			OnClickZoneOpenButtonDelegate.ExecuteIfBound(this);
		}
		else
		{
			bExceptConfirm = false;
		}
	};
	gWidgetMng.ShowSystemMessage(SystemParameter);
}
