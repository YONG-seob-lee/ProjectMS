// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_PlaySequenceWidget.h"

#include "Components/CheckBox.h"
#include "GameUserSettings/MS_GameUserSettings.h"

void UMS_PlaySequenceWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(!CPP_SequenceSkipCheckBox)
	{
		return;
	}
	
	CPP_SequenceSkipCheckBox->OnCheckStateChanged.AddUniqueDynamic(this, &UMS_PlaySequenceWidget::OnCheckChanged);
	
	const TObjectPtr<UMS_GameUserSettings> GameUserSettings = Cast<UMS_GameUserSettings>(GEngine->GetGameUserSettings());
	if(!GameUserSettings)
	{
		return;
	}
	if(GameUserSettings->IsPlaySequence())
	{
		CPP_SequenceSkipCheckBox->SetCheckedState(ECheckBoxState::Unchecked);
	}
	else
	{
		CPP_SequenceSkipCheckBox->SetCheckedState(ECheckBoxState::Checked);
	}
}

void UMS_PlaySequenceWidget::OnCheckChanged(bool IsChecked)
{
	const TObjectPtr<UMS_GameUserSettings> GameUserSettings = Cast<UMS_GameUserSettings>(GEngine->GetGameUserSettings());
	if(!GameUserSettings)
	{
		return;
	}
	
	if(IsChecked)
	{
		GameUserSettings->SetIsPlaySequence(false);
	}
	else
	{
		GameUserSettings->SetIsPlaySequence(true);
	}
}
