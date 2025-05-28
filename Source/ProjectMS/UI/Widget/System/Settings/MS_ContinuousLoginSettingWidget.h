// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_CheckBoxItemBase.h"
#include "MS_ContinuousLoginSettingWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_ContinuousLoginSettingWidget : public UMS_CheckBoxItemBase
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	virtual void OnCheckChanged(bool IsChecked) override;
};
