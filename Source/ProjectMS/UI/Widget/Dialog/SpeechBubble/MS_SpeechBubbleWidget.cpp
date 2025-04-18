﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_SpeechBubbleWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Widget/WidgetComponent/MS_WidgetSwitcher.h"

void UMS_SpeechBubbleWidget::NativeConstruct()
{
	Super::NativeConstruct();

	bIsConstructed = true;
}

void UMS_SpeechBubbleWidget::SetText(const FText& SpeechString) const
{
	CPP_SpeechSwitcher->SetActiveWidgetIndex(0);
	if(CPP_Speech)
	{
		CPP_Speech->SetText(SpeechString);
	}
}

void UMS_SpeechBubbleWidget::SetImage(EMS_SpeechImageType aSpeechImageType)
{
	CPP_SpeechSwitcher->SetActiveWidgetIndex(1);

	UTexture2D* ImageImage = nullptr;
	ImageType = aSpeechImageType;
	switch (aSpeechImageType)
	{
	case EMS_SpeechImageType::PutDownItems:
		{
			ImageImage = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *SpeechImagePath::PutDownItems));
			LoopIdleTime = 1;
			break;
		}
	case EMS_SpeechImageType::Pay:
		{
			ImageImage = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *SpeechImagePath::Pay));
			LoopIdleTime = 1;
			break;
		}
	case EMS_SpeechImageType::Angry:
		{
			ImageImage = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, *SpeechImagePath::Angry));
			LoopIdleTime = 20;
			break;
		}
	default:
		{
			break;
		}
	}

	CPP_Image->SetBrushFromTexture(ImageImage);
}

void UMS_SpeechBubbleWidget::OnAnimationStarted_Implementation(const UWidgetAnimation* Animation)
{
	Super::OnAnimationStarted_Implementation(Animation);
}

void UMS_SpeechBubbleWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
	Super::OnAnimationFinished_Implementation(Animation);

	if(Animation == SpeechBubbleStart)
	{
		if(ImageType == EMS_SpeechImageType::PutDownItems)
		{
			PlayAnimation(SpeechBubbleIdle_PutDownItems);
		}
		else
		{
			PlayAnimation(SpeechBubbleIdle, 0.f, LoopIdleTime);
		}
	}
	else if(Animation == SpeechBubbleIdle || Animation == SpeechBubbleIdle_PutDownItems)
	{
		ImageType = EMS_SpeechImageType::None;
		PlayAnimation(SpeechBubbleEnd);
	}
}

void UMS_SpeechBubbleWidget::PlaySpeech()
{
	PlayAnimation(SpeechBubbleStart);
}