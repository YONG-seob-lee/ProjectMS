// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_PlaySequenceWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_PlaySequenceWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	
private:
	UFUNCTION()
	void OnCheckChanged(bool IsChecked);
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UCheckBox> CPP_SequenceSkipCheckBox = nullptr;
};
