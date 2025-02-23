// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_DefaultLoadingWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_DefaultLoadingWidget : public UMS_Widget
{
	GENERATED_BODY()
public:

private:
	UPROPERTY()
	TObjectPtr<class UMS_LoadingTutorialWidget> CPP_LoadingTutorialWidget = nullptr;
};
