// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_DescriptionWidget.h"

#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/TextBlock.h"

void UMS_DescriptionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	FillDefaultAnimations();
}

void UMS_DescriptionWidget::OnAnimFinished(const FName& aAnimName)
{
	Super::OnAnimFinished(aAnimName);

	if(aAnimName == DescAnim::DotAnimationUpToRight || aAnimName == DescAnim::DotAnimationDownToRight || aAnimName == DescAnim::DotAnimationUpToLeft || aAnimName == DescAnim::DotAnimationDownToLeft)
	{
		Stop();
	}
	else if(aAnimName == DescAnim::StartUpToRight)
	{
		PlayAnimationByName(DescAnim::DotAnimationUpToRight, 0.f, 5);
	}
	else if(aAnimName == DescAnim::StartDownToRight)
	{
		PlayAnimationByName(DescAnim::DotAnimationDownToRight, 0.f, 5);
	}
	else if(aAnimName == DescAnim::StartUpToLeft)
	{
		PlayAnimationByName(DescAnim::DotAnimationUpToLeft, 0.f, 5);
	}
	else if(aAnimName == DescAnim::StartDownToLeft)
	{
		PlayAnimationByName(DescAnim::DotAnimationDownToLeft, 0.f, 5);
	}
	else if(aAnimName == DescAnim::StopUpToRight || aAnimName == DescAnim::StopDownToRight || aAnimName == DescAnim::StopUpToLeft || aAnimName == DescAnim::StopDownToLeft)
	{
		if(OnFinishedTutorialCallback)
		{
			OnFinishedTutorialCallback();
		}
		SetVisibility(ESlateVisibility::Collapsed);
		RemoveFromParent();
	}
}

void UMS_DescriptionWidget::Start(EMS_TutorialDirection aDirection, const FText& Desc, const FText& SubDesc)
{
	TargetDirection = aDirection;
	SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	CPP_Desc->SetText(Desc);
	CPP_SubDesc->SetText(SubDesc);

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
	else if(TargetDirection == EMS_TutorialDirection::UpToLeft)
	{
		PlayAnimationByName(DescAnim::StopUpToLeft);
	}
	else if(TargetDirection == EMS_TutorialDirection::DownToLeft)
	{
		PlayAnimationByName(DescAnim::StopDownToLeft);
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
	else if(aDirection == EMS_TutorialDirection::UpToLeft)
	{
		PlayAnimationByName(DescAnim::StartUpToLeft);
	}
	else if(aDirection == EMS_TutorialDirection::DownToLeft)
	{
		PlayAnimationByName(DescAnim::StartDownToLeft);
	}
}
