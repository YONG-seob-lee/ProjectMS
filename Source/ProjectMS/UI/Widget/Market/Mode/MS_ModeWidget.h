// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "ContentsUtilities/MS_GameProcessDefine.h"
#include "MS_ModeWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_ModeWidget : public UMS_Widget
{
	GENERATED_BODY()

public:
	virtual void OnChangeMode(EMS_ModeState aModeState) {}
};
