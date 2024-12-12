// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_ModalWidget.generated.h"

struct FMS_ModalData
{
	FMS_ModalData();
};

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_ModalWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	
	void SetModal(FMS_ModalData* aModalData);
	
private:
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_Button> CPP_BlurButton = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_InModalWidget> CPP_InModalWidget = nullptr;
};
