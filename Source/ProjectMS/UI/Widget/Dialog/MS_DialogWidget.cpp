// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_DialogWidget.h"

#include "MS_Define.h"
#include "MS_DialogPortraitWidget.h"
#include "Button/MS_Button.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"
#include "Widget/System/Toturial/MS_DescriptionWidget.h"

namespace DialogNumber
{
	constexpr int32 First = 0;
}

FMS_DialogParameter::FMS_DialogParameter(const FString& aTypeText, float aTypeSpeed)
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
		PlayTyping();
	}
	else if(aAnimName == DialogAnimation::Close)
	{
		SetVisibility(ESlateVisibility::Collapsed);
		DialogParameters[ProcessingDialogNumber].FinishDialogEvent();
		ProcessingDialogNumber = INDEX_NONE;
	}
}

void UMS_DialogWidget::RequestDialog(const TArray<FMS_DialogParameter>& aDialogParameters)
{
	SetVisibility(ESlateVisibility::Visible);
	DialogParameters = aDialogParameters;
	ProcessingDialogNumber = 0;

	for(int32 i = 0 ; i < DialogParameters.Num(); i++)
	{
		if(DialogParameters.IsValidIndex(i))
		{
			DialogParameters[i].SetIsLeft(i % 2 == 0);
		}
	}
	
	if(DialogParameters.IsValidIndex(ProcessingDialogNumber))
	{
		CPP_DialogText->SetText(FText::FromString(DialogParameters[ProcessingDialogNumber].ShowType()));
		PlayAnimationByName(DialogAnimation::Start);
	}
}

void UMS_DialogWidget::PlayTyping()
{
	if(DialogParameters.IsValidIndex(ProcessingDialogNumber))
	{
		MS_LOG(TEXT("Start Dialog Typing."));
		DialogParameters[ProcessingDialogNumber].SetDialogType(EMS_DialogType::Process);
		CPP_SkipButton->SetVisibility(ESlateVisibility::Visible);
		PlayPortrait(DialogParameters[ProcessingDialogNumber].IsLeft());
		ProcessTyping();
	}
}

void UMS_DialogWidget::ProcessTyping()
{
	if(DialogParameters.IsValidIndex(ProcessingDialogNumber) == false)
	{
		return;
	}
	
	if(DialogParameters[ProcessingDialogNumber].IsTypingEnd())
	{
		FinishedTyping();
		GetWorld()->GetTimerManager().ClearTimer(DialogTextTimerHandler);
		return;
	}
	
	const FString ShowType = DialogParameters[ProcessingDialogNumber].ShowType();
	CPP_DialogText->SetText(FText::FromString(ShowType));
	DialogParameters[ProcessingDialogNumber].AddProcess();
	GetWorld()->GetTimerManager().SetTimer(DialogTextTimerHandler, this, &UMS_DialogWidget::ProcessTyping, DialogParameters[ProcessingDialogNumber].GetTypeSpeed(), false);
}

void UMS_DialogWidget::FinishedTyping()
{
	if(DialogParameters.IsValidIndex(ProcessingDialogNumber))
	{
		DialogParameters[ProcessingDialogNumber].SetDialogType(EMS_DialogType::Finished);
		GetWorld()->GetTimerManager().ClearTimer(DialogTextTimerHandler);
		CPP_SkipPanel->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		PlayAnimationByName(DialogAnimation::SkipAnimation, 0.f, 999999);

		FinishedPortrait(DialogParameters[ProcessingDialogNumber].IsLeft());
	}
}

void UMS_DialogWidget::PlayPortrait(bool bIsLeft) const
{
	if(bIsLeft)
	{
		CPP_LeftPortraitWidget->PlayMouse();
	}
	else
	{
		CPP_RightPortraitWidget->PlayMouse();
	}
}

void UMS_DialogWidget::FinishedPortrait(bool bIsLeft) const
{
	if(bIsLeft)
	{
		CPP_LeftPortraitWidget->StopMouse();
	}
	else
	{
		CPP_RightPortraitWidget->StopMouse();
	}
}

void UMS_DialogWidget::OnClickedSkipButton()
{
	if(DialogParameters.IsValidIndex(ProcessingDialogNumber) == false)
	{
		return;
	}
	
	if(DialogParameters[ProcessingDialogNumber].GetDialogType() == EMS_DialogType::Process)
	{
		FinishedTyping();
		CPP_DialogText->SetText(FText::FromString(DialogParameters[ProcessingDialogNumber].ShowFullType()));
	}
	else if(DialogParameters[ProcessingDialogNumber].GetDialogType() == EMS_DialogType::Finished)
	{
		if(DialogParameters.IsValidIndex(ProcessingDialogNumber + 1))
		{
			ProcessingDialogNumber += 1;
			PlayTyping();
		}
		else
		{
			StopAllAnimations();
			PlayAnimationByName(DialogAnimation::Close);
			CPP_SkipPanel->SetVisibility(ESlateVisibility::Collapsed);
			CPP_SkipButton->SetVisibility(ESlateVisibility::Collapsed);
			MS_LOG(TEXT("Finished Dialog Typing."));	
		}
	}
}
