// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_PreviewWidget.h"

#include "Button/MS_Button.h"

void UMS_PreviewWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	CPP_ApplyButton->GetOnClickedDelegate().AddUObject(this, &UMS_PreviewWidget::OnClickApplyButton);
	CPP_CancelButton->GetOnClickedDelegate().AddUObject(this, &UMS_PreviewWidget::OnClickCancelButton);
}

void UMS_PreviewWidget::OnClickApplyButton()
{
	OnClickApplyButtonDelegate.ExecuteIfBound(this);
}

void UMS_PreviewWidget::OnClickCancelButton()
{
	OnClickCancelButtonDelegate.ExecuteIfBound(this);
}
