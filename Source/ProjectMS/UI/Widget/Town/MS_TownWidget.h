// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_TownWidget.generated.h"

enum class EMS_ModeState : uint8;
enum class EMS_ControllerModeType : uint8;

namespace ModePanelAnimation
{
	const FName IdleMode = FName(TEXT("IdleMode"));
	const FName SetMode = FName(TEXT("SetMode"));
	const FName UnSetMode = FName(TEXT("UnSetMode"));
}
/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_TownWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	static FName GetWidgetName() { return TEXT("Town"); }

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UMS_TimeLineWidget> CPP_TimeLineWidget = nullptr;
};