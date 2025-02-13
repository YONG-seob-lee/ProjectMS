// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_DescriptionWidget.h"

#include "Components/TextBlock.h"

void UMS_DescriptionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	FillDefaultAnimations();
	SetVisibility(ESlateVisibility::Collapsed);
}

void UMS_DescriptionWidget::OnAnimFinished(const FName& aAnimName)
{
	Super::OnAnimFinished(aAnimName);

	if(aAnimName == DescAnim::DotAnimation)
	{
		Stop();
	}
	else if(aAnimName == DescAnim::StopTutorial)
	{
		if(OnFinishedTutorialCallback)
		{
			OnFinishedTutorialCallback();
		}
		SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UMS_DescriptionWidget::Start(const FString& Desc, const FString& SubDesc)
{
	SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	CPP_Desc->SetText(FText::FromString(Desc));
	CPP_SubDesc->SetText(FText::FromString(SubDesc));
	
	PlayAnimationByName(DescAnim::StartTutorial);
	PlayAnimationByName(DescAnim::DotAnimation, 0.f, 5);
}

void UMS_DescriptionWidget::Stop()
{
	PlayAnimationByName(DescAnim::StopTutorial);
}
