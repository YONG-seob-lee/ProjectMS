// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_SettingModalWidget.h"

#include "MS_Define.h"
#include "Widget/ListViewElement/ElementData/MS_SliderSystemElementData.h"
#include "Widget/WidgetComponent/MS_ListView.h"

void UMS_SettingModalWidget::InitWidget(const FName& aTypeName, bool bManaged, bool bAttachToRoot)
{
	Super::InitWidget(aTypeName, bManaged, bAttachToRoot);

	TMap<int32, float> DefaultSoundVolume;
	gSoundMng.GetAllDefaultVolume(DefaultSoundVolume);
	DefaultSoundVolume.KeySort([](int32 lv, int32 rv) { return lv < rv; });
	for(const auto& SoundVolume : DefaultSoundVolume)
	{
		if(static_cast<EMS_SoundClassType>(SoundVolume.Key) == EMS_SoundClassType::Undefined)
		{
			continue;
		}
		if(UMS_SliderSystemElementData* Data = MS_NewObject<UMS_SliderSystemElementData>(this))
		{
			Data->SetSettingName(GetSoundName(static_cast<EMS_SoundClassType>(SoundVolume.Key)));
			Data->SetValue(SoundVolume.Value);
			Data->SetSoundType(static_cast<EMS_SoundClassType>(SoundVolume.Key));
			SoundSliderDatas.Emplace(Data);
		}
	}
	
	CPP_SoundListView->SetListItems(SoundSliderDatas);
}

void UMS_SettingModalWidget::FinishWidget()
{
	for(const auto& SoundSliderData : SoundSliderDatas)
	{
		MS_DeleteObject(SoundSliderData);
	}

	SoundSliderDatas.Empty();
	
	Super::FinishWidget();
}

FString UMS_SettingModalWidget::GetSoundName(EMS_SoundClassType aSoundType)
{
	switch (aSoundType)
	{
	case EMS_SoundClassType::Master:
		return TEXT("마스터 음량");
	case EMS_SoundClassType::BGM:
		return TEXT("BGM 음량");
	case EMS_SoundClassType::Ambient:
		return TEXT("환경음 음량");
	case EMS_SoundClassType::Voice:
		return TEXT("오리 음량");
	case EMS_SoundClassType::UserInterface:
		return TEXT("터치 이펙트 음량");
	default:
		return FString();
	}
}
