// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_SystemMessageWidget.h"

#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"

void UMS_SystemMessageWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CPP_Desc->SetAutoWrapText(true);
}

void UMS_SystemMessageWidget::InitSystemMessage(const FMS_SystemParameter& SystemParameter)
{
	if(SystemParameter.bUseBlurButton)
	{
		CPP_BlurButton->GetOnClickedDelegate().AddUObject(this, &UMS_SystemMessageWidget::CloseWidget);
	}
	if(SystemParameter.bShowExitButton)
	{
		CPP_ExitButton->SetVisibility(ESlateVisibility::Visible);
		CPP_ExitButton->GetOnClickedDelegate().AddUObject(this, &UMS_SystemMessageWidget::CloseWidget);
	}
	else
	{
		CPP_ExitButton->SetVisibility(ESlateVisibility::Collapsed);
	}
	
	CPP_Title->SetText(FText::FromString(SystemParameter.Title));
	CPP_SubTitle->SetText(FText::FromString(SystemParameter.SubTitle));
	CPP_Desc->SetText(FText::FromString(SystemParameter.Desc));
	CPP_DenyReason->SetText(FText::FromString(SystemParameter.Deny));

	if(SystemParameter.InteractButtonType == EMS_InteractButtonType::None)
	{
		CPP_InteractButtonPanel->SetVisibility(ESlateVisibility::Collapsed);
	}
	else if(SystemParameter.InteractButtonType == EMS_InteractButtonType::OnlyConfirm)
	{
		CPP_ConfirmButton->GetOnClickedDelegate().AddUObject(this, &UMS_SystemMessageWidget::OnClickedConfirmButton);
		CPP_CancelButton->SetVisibility(ESlateVisibility::Collapsed);
	}
	else if(SystemParameter.InteractButtonType == EMS_InteractButtonType::OnlyCancel)
	{
		CPP_ConfirmButton->SetVisibility(ESlateVisibility::Collapsed);
		CPP_CancelButton->GetOnClickedDelegate().AddUObject(this, &UMS_SystemMessageWidget::OnClickedCancelButton);
	}
	else
	{
		CPP_ConfirmButton->GetOnClickedDelegate().AddUObject(this, &UMS_SystemMessageWidget::OnClickedConfirmButton);
		CPP_CancelButton->GetOnClickedDelegate().AddUObject(this, &UMS_SystemMessageWidget::OnClickedCancelButton);
		CPP_InteractButtonPanel->SetVisibility(ESlateVisibility::Visible);
	}

	OnClickedConfirmButtonCallback = SystemParameter.OnClickedConfirmButtonCallback;
	OnClickedCancelButtonCallback = SystemParameter.OnClickedCancelButtonCallback;
}

void UMS_SystemMessageWidget::CloseWidget()
{
	gWidgetMng.DestroyWidget(this);
}

void UMS_SystemMessageWidget::OnClickedConfirmButton()
{
	if(OnClickedConfirmButtonCallback)
	{
		bool bExceptConfirm;
		OnClickedConfirmButtonCallback(bExceptConfirm);
		if(bExceptConfirm)
		{
			OnClickedConfirmButtonCallback = nullptr;
			gWidgetMng.DestroyWidget(this);
		}
		else
		{
			PlayAnimationByName(SystemMessageAnimation::ShakeSystemMessage);

			if(CPP_DenyReason->GetText().ToString().IsEmpty() == false || CPP_DenyReason->IsVisible() == false)
			{
				PlayAnimationByName(SystemMessageAnimation::Deny);
			}
		}
	}
}

void UMS_SystemMessageWidget::OnClickedCancelButton()
{
	if(OnClickedCancelButtonCallback)
	{
		OnClickedCancelButtonCallback();
		OnClickedCancelButtonCallback = nullptr;
	}
	gWidgetMng.DestroyWidget(this);
}
