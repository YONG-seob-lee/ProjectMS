// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ArrangementWidget.h"

#include "Button/MS_Button.h"


void UMS_ArrangementWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	CPP_ApplyButton->GetOnClickedDelegate().AddUObject(this, &UMS_ArrangementWidget::OnClickApplyButton);
	CPP_CancelButton->GetOnClickedDelegate().AddUObject(this, &UMS_ArrangementWidget::OnClickCancelButton);
	CPP_RotateButton->GetOnClickedDelegate().AddUObject(this, &UMS_ArrangementWidget::OnClickRotateButton);
}

void UMS_ArrangementWidget::OnClickApplyButton()
{
	OnClickApplyButtonDelegate.ExecuteIfBound(this);
}

void UMS_ArrangementWidget::OnClickCancelButton()
{
	OnClickCancelButtonDelegate.ExecuteIfBound(this);
}

void UMS_ArrangementWidget::OnClickRotateButton()
{
	OnClickRotateButtonDelegate.ExecuteIfBound(this);
}
