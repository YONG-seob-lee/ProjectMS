﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_AccountWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_AccountWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	static FName GetWidgetName() { return TEXT("Account"); }
	virtual void InitWidget(const FName& aTypeName, bool bManaged, bool bActivate) override;
	virtual void NativeConstruct() override;
	
private:
	void OnClickAccountButton();

	void OnGoogleLoginComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& ErrorStr);
	void LoginWithGoogle();
	void PlayNextStep() const;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_AccountButton> CPP_AccountButton = nullptr;
};
