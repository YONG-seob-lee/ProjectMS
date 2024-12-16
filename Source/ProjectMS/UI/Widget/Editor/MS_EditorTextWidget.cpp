// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_EditorTextWidget.h"

#include "Components/TextBlock.h"

UMS_EditorTextWidget::UMS_EditorTextWidget(const FObjectInitializer& aObjectInitializer)
	: Super(aObjectInitializer)
{
}

void UMS_EditorTextWidget::SetText(FString aText)
{
	TextBlock->SetText(FText::FromString(aText));
}
