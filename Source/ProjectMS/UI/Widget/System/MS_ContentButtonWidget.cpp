// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ContentButtonWidget.h"

#include "Button/MS_Button.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Widget/Town/Extension/MS_ExtensionWidget.h"

void UMS_ContentButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	FillDefaultAnimations();
}

void UMS_ContentButtonWidget::SetIconImage(UTexture2D* aIconImage) const
{
	if(CPP_IconImage)
	{
		CPP_IconImage->SetBrushFromTexture(aIconImage);
	}
}

void UMS_ContentButtonWidget::SetVerticalBoxVisibility(bool bShow) const
{
	if(CPP_ExtensionPanel)
	{
		CPP_ExtensionPanel->SetVisibility(bShow ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Collapsed);
	}
}

void UMS_ContentButtonWidget::OnAnimFinished(const FName& aAnimName)
{
	Super::OnAnimFinished(aAnimName);

	if(aAnimName == ExtensionAnim::CloseExtension)
	{
		SetVerticalBoxVisibility(false);
	}
}

UCommonButtonBase::FCommonButtonEvent& UMS_ContentButtonWidget::GetOnClickedDelegate() const
{
	return CPP_ContentButton->GetOnClickedDelegate();
}

void UMS_ContentButtonWidget::OpenExtensionUI()
{
	if(bOpen)
	{
		PlayAnimationByName(ExtensionAnim::CloseExtension);
		bOpen = false;
	}
	else
	{
		SetVerticalBoxVisibility(true);
		PlayAnimationByName(ExtensionAnim::OpenExtension);
		bOpen = true;
	}
}
