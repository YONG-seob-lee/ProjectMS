#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget/XEditorUtilityWidget.h"
#include "XDebugDialogueEditorUtilityWidget.generated.h"

UCLASS() class UXDebugDialogueEditorUtilityWidget : public UXEditorUtilityWidget
{
	GENERATED_BODY()

public:
	UXDebugDialogueEditorUtilityWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION() void OnActorSpawnerSectionEditorUtilityButtonClick();
	UFUNCTION() void OnModeConverterSectionEditorUtilityButtonClick();
	UFUNCTION() void OnScriptExecutorSectionEditorUtilityButtonClick();
	UFUNCTION() void OnDataRefresherSectionEditorUtilityButtonClick();

	// Property
public:
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category="WidgetComponent") class UHorizontalBox* SectionEditorUtilityButtonFrameHorizontalBox = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category="WidgetComponent") class UEditorUtilityButton* ActorSpawnerSectionEditorUtilityButton = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category="WidgetComponent") class UTextBlock* ActorSpawnerSectionEditorUtilityButtonLabelTextBlock = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category="WidgetComponent") class UEditorUtilityButton* ModeConverterSectionEditorUtilityButton = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category="WidgetComponent") class UTextBlock* ModeConverterSectionEditorUtilityButtonLabelTextBlock = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category="WidgetComponent") class UEditorUtilityButton* ScriptExecutorSectionEditorUtilityButton = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category="WidgetComponent") class UTextBlock* ScriptExecutorSectionEditorUtilityButtonLabelTextBlock = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category="WidgetComponent") class UEditorUtilityButton* DataRefresherSectionEditorUtilityButton = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category="WidgetComponent") class UTextBlock* DataRefresherSectionEditorUtilityButtonLabelTextBlock = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category="WidgetComponent") class UCanvasPanel* SectionFrameCanvasPanel = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category="WidgetComponent") class UWidgetSwitcher* SectionFrameWidgetSwitcher = nullptr;
};