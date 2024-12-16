// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_ModeNameWidget.generated.h"

/**
 * 
 */
enum class EMS_ModeState : uint8;
enum class EMS_ControllerModeType : uint8;

UCLASS()
class PROJECTMS_API UMS_ModeNameWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	
	void OnChangeMode(EMS_ModeState aModeState, EMS_ControllerModeType aControllerModeType);
	
private:
	void SetModeName(const FString& aModeName) const;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_ModeText = nullptr;
};
