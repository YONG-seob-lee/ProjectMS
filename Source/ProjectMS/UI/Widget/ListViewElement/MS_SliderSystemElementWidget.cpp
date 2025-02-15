// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_SliderSystemElementWidget.h"

#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "ElementData/MS_SliderSystemElementData.h"
#include "Manager_Client/MS_SoundManager.h"
#include "GameUserSettings/MS_GameUserSettings.h"

void UMS_SliderSystemElementWidget::NativeConstruct()
{
	Super::NativeConstruct();

	CPP_Slider->OnValueChanged.AddUniqueDynamic(this, &UMS_SliderSystemElementWidget::OnValueChanged);
}

void UMS_SliderSystemElementWidget::NativeOnListItemObjectSet(UObject* aListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(aListItemObject);

	if(const TObjectPtr<UMS_SliderSystemElementData> Data = Cast<UMS_SliderSystemElementData>(aListItemObject))
	{
		if(CPP_SliderSystemName)
		{
			CPP_SliderSystemName->SetText(FText::FromString(Data->GetSettingName()));
		}
		if(CPP_Slider)
		{
			CPP_Slider->SetValue(Data->GetValue());
			OnValueChanged(Data->GetValue());
		}
		SoundType = Data->GetSoundType();
	}
}

void UMS_SliderSystemElementWidget::OnValueChanged(float aValue)
{
	gSoundMng.AdjustSoundVolume(SoundType, aValue);

	const FString CurrentValue = TEXT("\"") + FString::FromInt(aValue * 100) + TEXT("\"");
	CPP_CurrentValue->SetText(FText::FromString(CurrentValue));

	if(const TObjectPtr<UMS_GameUserSettings> GameUserSettings = Cast<UMS_GameUserSettings>(GEngine->GetGameUserSettings()))
	{
		GameUserSettings->UpdateDefaultSoundVolume(SoundType, aValue);
	}
}
