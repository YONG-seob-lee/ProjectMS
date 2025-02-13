// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_DialogWidget.h"

#include "MS_Define.h"
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

void UMS_DialogWidget::InitWidget(const FName& aTypeName, bool bManaged, bool bAttachToRoot)
{
	Super::InitWidget(aTypeName, bManaged, bAttachToRoot);
}

void UMS_DialogWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if(CPP_DialogText)
	{
		CPP_DialogText->SetAutoWrapText(true);
	}

	FillDefaultAnimations();
}

void UMS_DialogWidget::OnAnimFinished(const FName& aAnimName)
{
	Super::OnAnimFinished(aAnimName);

	if(aAnimName == DialogAnimation::Start)
	{
		MS_LOG(TEXT("Start Dialog Typing."));
		ProcessTyping();
	}
	else if(aAnimName == DialogAnimation::Close)
	{
		DialogParameter.FinishDialogEvent();
	}
}

void UMS_DialogWidget::RequestDialog(const FMS_DialogParameter& aDialogParameter)
{
	DialogParameter = aDialogParameter;
	CPP_DialogText->SetText(FText::FromString(DialogParameter.ShowType()));
	PlayAnimationByName(DialogAnimation::Start);
}

void UMS_DialogWidget::ProcessTyping()
{
	if(DialogParameter.IsFinishType())
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
	GetWorld()->GetTimerManager().ClearTimer(DialogTextTimerHandler);
	PlayAnimationByName(DialogAnimation::Close);
	MS_LOG(TEXT("Finished Dialog Typing."));
}
