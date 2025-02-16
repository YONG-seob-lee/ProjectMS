// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_TutorialSkipSettingWidget.h"

#include "Components/CheckBox.h"
#include "GameUserSettings/MS_GameUserSettings.h"

void UMS_TutorialSkipSettingWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(!CPP_TutorialSkipCheckBox)
	{
		return;
	}
	
	CPP_TutorialSkipCheckBox->OnCheckStateChanged.AddUniqueDynamic(this, &UMS_TutorialSkipSettingWidget::OnCheckChanged);
	
	const TObjectPtr<UMS_GameUserSettings> GameUserSettings = Cast<UMS_GameUserSettings>(GEngine->GetGameUserSettings());
	if(!GameUserSettings)
	{
		return;
	}
	if(GameUserSettings->IsAllProcessTutorialFinished())
	{
		CPP_TutorialSkipCheckBox->SetCheckedState(ECheckBoxState::Checked);
	}
	else
	{
		CPP_TutorialSkipCheckBox->SetCheckedState(ECheckBoxState::Unchecked);
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
