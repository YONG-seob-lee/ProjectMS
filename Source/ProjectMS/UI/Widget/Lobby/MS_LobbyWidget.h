// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_LobbyWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_LobbyWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	static FName GetWidgetName() { return TEXT("Lobby"); }
	virtual void NativeConstruct() override;

private:
	void OnClickedStartButton();
	void OnFinishedTransition();
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_Button> CPP_StartButton = nullptr;
};
