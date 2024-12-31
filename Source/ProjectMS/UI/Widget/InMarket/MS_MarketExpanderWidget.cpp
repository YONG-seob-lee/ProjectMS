// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_MarketExpanderWidget.h"

#include "Button/MS_Button.h"

namespace ArrowAnimation
{
	const FName Open = TEXT("Open");
	const FName Close = TEXT("Close");
}

void UMS_MarketExpanderWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	FillDefaultAnimations();

	CPP_ArrowButton->GetOnClickedDelegate().AddUObject(this, &UMS_MarketExpanderWidget::OnClickedArrowButton);
	CPP_ArrowButton->SetVisibility(ESlateVisibility::Visible);
}

void UMS_MarketExpanderWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UMS_MarketExpanderWidget::OnClickedArrowButton()
{
	if(bOpen)
	{
		PlayAnimationByName(ArrowAnimation::Close);
	}
	else
	{
		PlayAnimationByName(ArrowAnimation::Open);
	}

	bOpen = !bOpen;
}
