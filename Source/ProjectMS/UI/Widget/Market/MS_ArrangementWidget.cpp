// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ArrangementWidget.h"

#include "Button/MS_Button.h"


void UMS_ArrangementWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	CPP_ApplyButton->GetOnClickedDelegate().AddUObject(this, &UMS_ArrangementWidget::OnClickApplyButton);
	CPP_CancelButton->GetOnClickedDelegate().AddUObject(this, &UMS_ArrangementWidget::OnClickCancelButton);
}

void UMS_ArrangementWidget::OnClickApplyButton()
{
	OnClickApplyButtonDelegate.ExecuteIfBound(this);
}

void UMS_ArrangementWidget::OnClickCancelButton()
{
	OnClickCancelButtonDelegate.ExecuteIfBound(this);
}