// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ContentButtonWidget.h"

#include "MS_WidgetManager.h"
#include "Button/MS_Button.h"
#include "Components/Image.h"

void UMS_ContentButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if(CPP_ContentButton)
	{
		CPP_ContentButton->GetOnClickedDelegate().AddWeakLambda(this, [this]()
		{
			gWidgetMng.ShowToastMessage(TEXT(""));
		});
	}
}

void UMS_ContentButtonWidget::SetIconImage(UTexture2D* aIconImage) const
{
	if(CPP_IconImage)
	{
		CPP_IconImage->SetBrushFromTexture(aIconImage);
	}
}

UCommonButtonBase::FCommonButtonEvent& UMS_ContentButtonWidget::GetOnClickedDelegate() const
{
	return CPP_ContentButton->GetOnClickedDelegate();
}
