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

	if(aAnimName == DescAnim::DotAnimation_UpToRight || aAnimName == DescAnim::DotAnimation_DownToRight)
	{
		Stop();
	}
	else if(aAnimName == DescAnim::StartUpToRight)
	{
		PlayAnimationByName(DescAnim::DotAnimation_UpToRight, 0.f, 5);
	}
	else if(aAnimName == DescAnim::StartDownToRight)
	{
		PlayAnimationByName(DescAnim::DotAnimation_DownToRight, 0.f, 5);
	}
	else if(aAnimName == DescAnim::StopUpToRight || aAnimName == DescAnim::StopDownToRight)
	{
		if(OnFinishedTutorialCallback)
		{
			OnFinishedTutorialCallback();
		}
		SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UMS_DescriptionWidget::Start(EMS_TutorialDirection aDirection, const FString& Desc, const FString& SubDesc)
{
	TargetDirection = aDirection;
	SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	CPP_Desc->SetText(FText::FromString(Desc));
	CPP_SubDesc->SetText(FText::FromString(SubDesc));

	PlayDescription(aDirection);
}

void UMS_DescriptionWidget::Stop()
{
	if(TargetDirection == EMS_TutorialDirection::UpToRight)
	{
		PlayAnimationByName(DescAnim::StopUpToRight);
	}
	else if(TargetDirection == EMS_TutorialDirection::DownToRight)
	{
		PlayAnimationByName(DescAnim::StopDownToRight);
	}
}

void UMS_DescriptionWidget::PlayDescription(EMS_TutorialDirection aDirection)
{
	if(aDirection == EMS_TutorialDirection::UpToRight)
	{
		PlayAnimationByName(DescAnim::StartUpToRight);
	}
	else if (aDirection == EMS_TutorialDirection::DownToRight)
	{
		PlayAnimationByName(DescAnim::StartDownToRight);
	}
}
