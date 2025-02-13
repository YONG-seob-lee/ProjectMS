// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_DialogWidget.h"

#include "MS_Define.h"
#include "Button/MS_Button.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"

FMS_DialogParameter::FMS_DialogParameter(const FString& aTypeText, float aTypeSpeed, TFunction<void()> aFunc)
{
	TypeText = aTypeText;
	TypeSpeed = aTypeSpeed;
	
	TotalTypeNumber = aTypeText.Len();

	const TCHAR* t = *aTypeText;
	
	for(int32 i = 0 ; i < TotalTypeNumber ; i++)
	{
		if(TypeText[i] == 58) // ASCII Code    ": = 58"
		{
			TypeText.FindChar(TypeText[i], ProcessNumber);
			break;
		}
	}

	DialogEndCallback = aFunc;
}

FString FMS_DialogParameter::ShowType() const
{
	return TypeText.Left(ProcessNumber);
}

void UMS_DialogWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if(CPP_DialogText)
	{
		CPP_DialogText->SetAutoWrapText(true);
	}

	if(CPP_SkipButton)
	{
		CPP_SkipButton->GetOnClickedDelegate().AddUObject(this, &UMS_DialogWidget::OnClickedSkipButton);
		CPP_SkipButton->SetVisibility(ESlateVisibility::Collapsed);
	}

	if(CPP_SkipPanel)
	{
		CPP_SkipPanel->SetVisibility(ESlateVisibility::Collapsed);
	}

	FillDefaultAnimations();

	SetVisibility(ESlateVisibility::Collapsed);
}

void UMS_DialogWidget::OnAnimFinished(const FName& aAnimName)
{
	Super::OnAnimFinished(aAnimName);

	if(aAnimName == DialogAnimation::Start)
	{
		MS_LOG(TEXT("Start Dialog Typing."));
		DialogParameter.SetDialogType(EMS_DialogType::Process);
		CPP_SkipButton->SetVisibility(ESlateVisibility::Visible);
		ProcessTyping();
	}
	else if(aAnimName == DialogAnimation::Close)
	{
		SetVisibility(ESlateVisibility::Collapsed);
		DialogParameter.FinishDialogEvent();
	}
}

void UMS_DialogWidget::RequestDialog(const FMS_DialogParameter& aDialogParameter)
{
	SetVisibility(ESlateVisibility::Visible);
	DialogParameter = aDialogParameter;
	CPP_DialogText->SetText(FText::FromString(DialogParameter.ShowType()));
	PlayAnimationByName(DialogAnimation::Start);
}

void UMS_DialogWidget::ProcessTyping()
{
	if(DialogParameter.IsTypingEnd())
	{
		FinishedTyping();
		GetWorld()->GetTimerManager().ClearTimer(DialogTextTimerHandler);
		return;
	}
	
	const FString ShowType = DialogParameter.ShowType();
	CPP_DialogText->SetText(FText::FromString(ShowType));
	DialogParameter.AddProcess();
	GetWorld()->GetTimerManager().SetTimer(DialogTextTimerHandler, this, &UMS_DialogWidget::ProcessTyping, DialogParameter.GetTypeSpeed(), false);
}

void UMS_DialogWidget::FinishedTyping()
{
	DialogParameter.SetDialogType(EMS_DialogType::Finished);
	GetWorld()->GetTimerManager().ClearTimer(DialogTextTimerHandler);
	CPP_SkipPanel->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	PlayAnimationByName(DialogAnimation::SkipAnimation, 0.f, 999999);
}

void UMS_DialogWidget::OnClickedSkipButton()
{
	if(DialogParameter.GetDialogType() == EMS_DialogType::Process)
	{
		FinishedTyping();
		CPP_DialogText->SetText(FText::FromString(DialogParameter.ShowFullType()));
	}
	else if(DialogParameter.GetDialogType() == EMS_DialogType::Finished)
	{
		StopAllAnimations();
		PlayAnimationByName(DialogAnimation::Close);
		CPP_SkipPanel->SetVisibility(ESlateVisibility::Collapsed);
		CPP_SkipButton->SetVisibility(ESlateVisibility::Collapsed);
		MS_LOG(TEXT("Finished Dialog Typing."));
	}
}
