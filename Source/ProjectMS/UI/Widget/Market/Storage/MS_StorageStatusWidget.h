// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_StorageStatusWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_StorageStatusWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	static FName GetWidgetName() { return TEXT("StorageStatus"); }
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	void OnClickedConfirmButton();

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_Button> CPP_ConfirmButton = nullptr;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_TileView> CPP_TileView = nullptr;
};