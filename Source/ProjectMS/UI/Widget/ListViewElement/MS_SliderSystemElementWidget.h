// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Manager_Client/MS_SoundManager.h"
#include "Widget/MS_Widget.h"
#include "MS_SliderSystemElementWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_SliderSystemElementWidget : public UMS_Widget, public IUserObjectListEntry
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void NativeOnListItemObjectSet(UObject* aListItemObject) override;

private:
	UFUNCTION()
	void OnValueChanged(float aValue);

	EMS_SoundClassType SoundType = EMS_SoundClassType::Undefined;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_SliderSystemName = nullptr;
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class USlider> CPP_Slider = nullptr;
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_CurrentValue = nullptr;
};
