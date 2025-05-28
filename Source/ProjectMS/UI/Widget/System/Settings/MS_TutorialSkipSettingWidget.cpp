// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_TutorialSkipSettingWidget.h"

#include "Components/CheckBox.h"
#include "GameUserSettings/MS_GameUserSettings.h"

void UMS_TutorialSkipSettingWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(!CPP_CheckBox)
	{
		return;
	}
	
	CPP_CheckBox->OnCheckStateChanged.AddUniqueDynamic(this, &UMS_TutorialSkipSettingWidget::OnCheckChanged);
	
	const TObjectPtr<UMS_GameUserSettings> GameUserSettings = Cast<UMS_GameUserSettings>(GEngine->GetGameUserSettings());
	if(!GameUserSettings)
	{
		return;
	}
	if(GameUserSettings->IsAllProcessTutorialFinished())
	{
		CPP_CheckBox->SetCheckedState(ECheckBoxState::Checked);
	}
	else
	{
		CPP_CheckBox->SetCheckedState(ECheckBoxState::Unchecked);
	}
}

void UMS_TutorialSkipSettingWidget::OnCheckChanged(bool IsChecked)
{
	const TObjectPtr<UMS_GameUserSettings> GameUserSettings = Cast<UMS_GameUserSettings>(GEngine->GetGameUserSettings());
	if(!GameUserSettings)
	{
		return;
	}
	
	if(IsChecked)
	{
		GameUserSettings->AllSkipProcessTutorial();
	}
	else
	{
		GameUserSettings->ResetProcessTutorial();
	}
}
