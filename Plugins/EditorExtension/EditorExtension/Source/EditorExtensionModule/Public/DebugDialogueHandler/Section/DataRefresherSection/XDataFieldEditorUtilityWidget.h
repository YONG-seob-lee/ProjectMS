#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "XDataFieldEditorUtilityWidget.generated.h"

UCLASS() class UXDataFieldEditorUtilityWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UXDataFieldEditorUtilityWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	// Property
public:
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UCanvasPanel* RootCanvasPanel = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UOverlay* DataFieldFrameOverlay = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UImage* DataTypeColorImage = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UHorizontalBox* TagFrameHorizontalBox = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UBorder* ContainerDataTypeFrameBorder = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UTextBlock* ContainerDataTypeTextBlock = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UTextBlock* DataNameTextBlock = nullptr;
};