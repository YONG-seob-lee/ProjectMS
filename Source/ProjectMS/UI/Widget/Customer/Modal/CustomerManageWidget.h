// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "CustomerManageWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UCustomerManageWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	static FName GetWidgetName() { return TEXT("CustomerManage");}

private:
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_CustomerButton> CPP_PersonChatButton = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<UMS_CustomerButton> CPP_PeopleChatButton = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_WidgetSwitcher> CPP_DetailWidgetSwitcher = nullptr;
};
