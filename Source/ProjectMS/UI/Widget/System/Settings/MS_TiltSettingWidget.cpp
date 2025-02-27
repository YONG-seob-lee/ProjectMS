// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_TiltSettingWidget.h"

#include "Components/CheckBox.h"
#include "Manager_Client/MS_PlayerCameraManager.h"

void UMS_TiltSettingWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CheckBoxes.Emplace(EMS_TiltType::VeryVeryLow, CPP_VVLow);
	CPP_VVLow->OnCheckStateChanged.AddUniqueDynamic(this, &UMS_TiltSettingWidget::OnCheckVVLow);
	CheckBoxes.Emplace(EMS_TiltType::VeryLow, CPP_VeryLow);
	CPP_VeryLow->OnCheckStateChanged.AddUniqueDynamic(this, &UMS_TiltSettingWidget::OnCheckVeryLow);
	CheckBoxes.Emplace(EMS_TiltType::Low, CPP_Low);
	CPP_Low->OnCheckStateChanged.AddUniqueDynamic(this, &UMS_TiltSettingWidget::OnCheckLow);
	CheckBoxes.Emplace(EMS_TiltType::Default, CPP_Default);
	CPP_Default->OnCheckStateChanged.AddUniqueDynamic(this, &UMS_TiltSettingWidget::OnCheckDefault);
	CheckBoxes.Emplace(EMS_TiltType::High, CPP_High);
	CPP_High->OnCheckStateChanged.AddUniqueDynamic(this, &UMS_TiltSettingWidget::OnCheckHigh);
	CheckBoxes.Emplace(EMS_TiltType::VeryHigh, CPP_VeryHigh);
	CPP_VeryHigh->OnCheckStateChanged.AddUniqueDynamic(this, &UMS_TiltSettingWidget::OnCheckVeryHigh);
	CheckBoxes.Emplace(EMS_TiltType::VeryVeryHigh, CPP_VVHigh);
	CPP_VVHigh->OnCheckStateChanged.AddUniqueDynamic(this, &UMS_TiltSettingWidget::OnCheckVVHigh);

	const TObjectPtr<UMS_GameUserSettings> GameUserSettings = Cast<UMS_GameUserSettings>(GEngine->GetGameUserSettings());
	if(!GameUserSettings)
	{
		return;
	}

	TargetTileType = GameUserSettings->GetQuarterViewCameraTiltType();
	for(const auto& CheckBox : CheckBoxes)
	{
		if(CheckBox.Key == TargetTileType)
		{
			CheckBox.Value->SetIsChecked(true);
		}
		else
		{
			CheckBox.Value->SetIsChecked(false);
		}
	}
}

void UMS_TiltSettingWidget::OnCheckVVLow(bool bIsChecked)
{
	if(bIsChecked)
	{
		TargetTileType = EMS_TiltType::VeryVeryLow;
		const TObjectPtr<UMS_GameUserSettings> GameUserSettings = Cast<UMS_GameUserSettings>(GEngine->GetGameUserSettings());
		if(!GameUserSettings)
		{
			return;
		}
		GameUserSettings->UpdateTiltType(EMS_TiltType::VeryVeryLow);
		GameUserSettings->ApplySettings(true);
		CPP_VVLow->SetIsChecked(true);
		gCameraMng.SetQuarterViewTilt(EMS_TiltType::VeryVeryLow);
	}
	RefreshCheckBoxes();
}
void UMS_TiltSettingWidget::OnCheckVeryLow(bool bIsChecked)
{
	if(bIsChecked)
	{
		TargetTileType = EMS_TiltType::VeryLow;
		const TObjectPtr<UMS_GameUserSettings> GameUserSettings = Cast<UMS_GameUserSettings>(GEngine->GetGameUserSettings());
		if(!GameUserSettings)
		{
			return;
		}
		GameUserSettings->UpdateTiltType(EMS_TiltType::VeryLow);
		GameUserSettings->ApplySettings(true);
		CPP_VeryLow->SetIsChecked(true);
		gCameraMng.SetQuarterViewTilt(EMS_TiltType::VeryLow);
	}
	RefreshCheckBoxes();
}

void UMS_TiltSettingWidget::OnCheckLow(bool bIsChecked)
{
	if(bIsChecked)
	{
		TargetTileType = EMS_TiltType::Low;
		const TObjectPtr<UMS_GameUserSettings> GameUserSettings = Cast<UMS_GameUserSettings>(GEngine->GetGameUserSettings());
		if(!GameUserSettings)
		{
			return;
		}
		GameUserSettings->UpdateTiltType(EMS_TiltType::Low);
		GameUserSettings->ApplySettings(true);
		CPP_Low->SetIsChecked(true);
		gCameraMng.SetQuarterViewTilt(EMS_TiltType::Low);
	}
	RefreshCheckBoxes();
}

void UMS_TiltSettingWidget::OnCheckDefault(bool bIsChecked)
{
	if(bIsChecked)
	{
		TargetTileType = EMS_TiltType::Default;
		const TObjectPtr<UMS_GameUserSettings> GameUserSettings = Cast<UMS_GameUserSettings>(GEngine->GetGameUserSettings());
		if(!GameUserSettings)
		{
			return;
		}
		GameUserSettings->UpdateTiltType(EMS_TiltType::Default);
		GameUserSettings->ApplySettings(true);
		CPP_Default->SetIsChecked(true);
		gCameraMng.SetQuarterViewTilt(EMS_TiltType::Default);
	}
	RefreshCheckBoxes();
}

void UMS_TiltSettingWidget::OnCheckHigh(bool bIsChecked)
{
	if(bIsChecked)
	{
		TargetTileType = EMS_TiltType::High;
		const TObjectPtr<UMS_GameUserSettings> GameUserSettings = Cast<UMS_GameUserSettings>(GEngine->GetGameUserSettings());
		if(!GameUserSettings)
		{
			return;
		}
		GameUserSettings->UpdateTiltType(EMS_TiltType::High);
		GameUserSettings->ApplySettings(true);
		CPP_High->SetIsChecked(true);
		gCameraMng.SetQuarterViewTilt(EMS_TiltType::High);
	}
	RefreshCheckBoxes();
}

void UMS_TiltSettingWidget::OnCheckVeryHigh(bool bIsChecked)
{
	if(bIsChecked)
	{
		TargetTileType = EMS_TiltType::VeryHigh;
		const TObjectPtr<UMS_GameUserSettings> GameUserSettings = Cast<UMS_GameUserSettings>(GEngine->GetGameUserSettings());
		if(!GameUserSettings)
		{
			return;
		}
		GameUserSettings->UpdateTiltType(EMS_TiltType::VeryHigh);
		GameUserSettings->ApplySettings(true);
		CPP_VeryHigh->SetIsChecked(true);
		gCameraMng.SetQuarterViewTilt(EMS_TiltType::VeryHigh);
	}
	RefreshCheckBoxes();
}

void UMS_TiltSettingWidget::OnCheckVVHigh(bool bIsChecked)
{
	if(bIsChecked)
	{
		TargetTileType = EMS_TiltType::VeryVeryHigh;
		const TObjectPtr<UMS_GameUserSettings> GameUserSettings = Cast<UMS_GameUserSettings>(GEngine->GetGameUserSettings());
		if(!GameUserSettings)
		{
			return;
		}
		GameUserSettings->UpdateTiltType(EMS_TiltType::VeryVeryHigh);
		GameUserSettings->ApplySettings(true);
		CPP_VVHigh->SetIsChecked(true);
		gCameraMng.SetQuarterViewTilt(EMS_TiltType::VeryVeryHigh);
	}
	RefreshCheckBoxes();
}

void UMS_TiltSettingWidget::RefreshCheckBoxes()
{
	for(const auto& CheckBox : CheckBoxes)
	{
		if(CheckBox.Key == TargetTileType)
		{
			CheckBox.Value->SetCheckedState(ECheckBoxState::Checked);
		}
		else
		{
			CheckBox.Value->SetCheckedState(ECheckBoxState::Unchecked);
		}
	}
}
