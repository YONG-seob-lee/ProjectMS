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
		if (aDenominator == -1)
		{
			CPP_CountText->SetText(FText::FromString(FString::Format(TEXT("{0} / 000"), {aMolecular})));
		}
		else
		{
			if (aMolecular == -1)
			{
				CPP_CountText->SetText(FText::FromString(FString::Format(TEXT("(교체중) / {0}"), {aDenominator})));
			}
			else
			{
				CPP_CountText->SetText(FText::FromString(FString::Format(TEXT("{0} / {1}"), {aMolecular, aDenominator})));
			}
		}
	}
}
