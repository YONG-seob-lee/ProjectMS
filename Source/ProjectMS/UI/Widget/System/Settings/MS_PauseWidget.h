// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_PauseWidget.generated.h"

namespace Dot
{
	constexpr int32 MaxCount = 4;
}
/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_PauseWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	static FSoftObjectPath GetWidgetPath() { return FSoftObjectPath(TEXT("/Game/UI/Widget/SystemWidgets/Setting/PauseWidget.PauseWidget")); }
	virtual void NativeConstruct() override;

private:
	void OnClickedBlurButton();
	void PauseTextAnimationTimer(float DeltaTime);

	FTSTicker::FDelegateHandle PauseHandle;
	int32 DotCount = 0;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_Button> CPP_BlurButton = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_PauseText = nullptr;
};
