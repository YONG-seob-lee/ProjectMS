// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_CountWidget.h"

#include "Components/TextBlock.h"

void UMS_CountWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetCount(1, 20);
}

void UMS_CountWidget::SetCount(int32 aMolecular, int32 aDenominator) const
{
	if(CPP_CountText)
	{
		CPP_CountText->SetText(FText::FromString(FString::Format(TEXT("{0} / {1}"), {aMolecular, aDenominator})));
	}
}
