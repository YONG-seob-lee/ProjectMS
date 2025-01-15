// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_Button.h"
#include "MS_ConfirmButton.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_ConfirmButton : public UMS_Button
{
	GENERATED_BODY()
public:
	void SetButtonName(const FString& aButtonString) const;
private:
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_ButtonName = nullptr;
};
