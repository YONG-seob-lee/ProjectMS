// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ContinuousLoginSettingWidget.h"

#include "Components/CheckBox.h"
#include "GameUserSettings/MS_GameUserSettings.h"

void UMS_ContinuousLoginSettingWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!CPP_CheckBox)
	{
		return;
	}

	CPP_CheckBox->OnCheckStateChanged.AddUniqueDynamic(this, &UMS_ContinuousLoginSettingWidget::OnCheckChanged);

	if (UMS_GameUserSettings* GameUserSettings = Cast<UMS_GameUserSettings>(GEngine->GetGameUserSettings()))
	{
		CPP_CheckBox->SetCheckedState(GameUserSettings->IsContinuousLogin() ? ECheckBoxState::Unchecked : ECheckBoxState::Checked);
	}
}

void UMS_ContinuousLoginSettingWidget::OnCheckChanged(bool IsChecked)
{
	if (UMS_GameUserSettings* GameUserSettings = Cast<UMS_GameUserSettings>(GEngine->GetGameUserSettings()))
	{
		// 체크가 되면 매번 로그인
		GameUserSettings->UpdateIsContinuousLogin(!IsChecked);
	}
}
