// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_MarketPlayButton.h"

#include "Components/TextBlock.h"

void UMS_MarketPlayButton::NativeConstruct()
{
	Super::NativeConstruct();
	
	CPP_ButtonText->SetText(FText::FromString(Text));
}

void UMS_MarketPlayButton::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	CPP_ButtonText->SetText(FText::FromString(Text));
}
