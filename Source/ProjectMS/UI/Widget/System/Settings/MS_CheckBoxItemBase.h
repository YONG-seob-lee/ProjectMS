// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_CheckBoxItemBase.generated.h"

/**
 * 
 */
class IMS_CheckBoxInterface
{
public:
	virtual ~IMS_CheckBoxInterface() = default;
	virtual void OnCheckChanged(bool IsChecked) = 0;
};

UCLASS(Abstract)
class PROJECTMS_API UMS_CheckBoxItemBase : public UMS_Widget, public IMS_CheckBoxInterface
{
	GENERATED_BODY()
public:
	virtual void OnCheckChanged(bool IsChecked) override {}

protected:
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UCheckBox> CPP_CheckBox = nullptr;
};
