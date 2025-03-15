// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "Widget/MS_Widget.h"
#include "MS_SystemMessageWidget.generated.h"

/**
 * 
 */
namespace SystemMessageAnimation
{
	const FName ShakeSystemMessage = TEXT("ShakeSystemMessage");
	const FName Deny = TEXT("Deny");
}

UCLASS()
class PROJECTMS_API UMS_SystemMessageWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	static FName GetWidgetName() { return TEXT("SystemMessage"); }

	virtual void NativeConstruct() override;

	void InitSystemMessage(const FMS_SystemParameter& SystemParameter);
	
private:
	void CloseWidget();

	void OnClickedConfirmButton();
	void OnClickedCancelButton();

	TFunction<void(bool&)> OnClickedConfirmButtonCallback = nullptr;;
	TFunction<void()> OnClickedCancelButtonCallback = nullptr;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_Button> CPP_BlurButton = nullptr;

	UPROPERTY(Meta = (BindWidget))
    TObjectPtr<class UMS_Button> CPP_ExitButton = nullptr;
    	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_Title = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_SubTitle = nullptr;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_Desc = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_DenyReason = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UCanvasPanel> CPP_InteractButtonPanel = nullptr;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_Button> CPP_ConfirmButton = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_Button> CPP_CancelButton = nullptr;
};
