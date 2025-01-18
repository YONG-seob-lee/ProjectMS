// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_StaffDetailWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_StaffDetailWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	
private:
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_ListView> CPP_AbilityListView = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_Button> CPP_HireButton = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_Button> CPP_ReconsiderButton = nullptr;
};
