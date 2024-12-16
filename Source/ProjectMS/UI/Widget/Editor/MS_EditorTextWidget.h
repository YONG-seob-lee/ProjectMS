// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_EditorTextWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_EditorTextWidget : public UMS_Widget
{
	GENERATED_BODY()

public:
	UMS_EditorTextWidget(const FObjectInitializer& aObjectInitializer);

	void SetText(FString aText);
	
private:
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> TextBlock = nullptr;
};
