// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager_Client/MS_SoundManager.h"
#include "Widget/MS_Widget.h"
#include "MS_SettingModalWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_SettingModalWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	static FName GetWidgetName() { return TEXT("Setting"); }

	virtual void InitWidget(const FName& aTypeName, bool bManaged, bool bAttachToRoot) override;
	virtual void FinishWidget() override;
	
private:
	FString GetSoundName(EMS_SoundClassType aSoundType);
	
	TArray<class UMS_SliderSystemElementData*> SoundSliderDatas = {};
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_ListView> CPP_SoundListView = nullptr;
};
