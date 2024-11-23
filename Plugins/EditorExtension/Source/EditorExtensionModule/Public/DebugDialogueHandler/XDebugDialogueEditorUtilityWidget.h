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
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UHorizontalBox* SectionEditorUtilityButtonFrameHorizontalBox = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UEditorUtilityButton* ActorSpawnerSectionEditorUtilityButton = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UTextBlock* ActorSpawnerSectionEditorUtilityButtonLabelTextBlock = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UEditorUtilityButton* ModeConverterSectionEditorUtilityButton = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UTextBlock* ModeConverterSectionEditorUtilityButtonLabelTextBlock = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UEditorUtilityButton* ScriptExecutorSectionEditorUtilityButton = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UTextBlock* ScriptExecutorSectionEditorUtilityButtonLabelTextBlock = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UEditorUtilityButton* DataRefresherSectionEditorUtilityButton = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UTextBlock* DataRefresherSectionEditorUtilityButtonLabelTextBlock = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UCanvasPanel* SectionFrameCanvasPanel = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UWidgetSwitcher* SectionFrameWidgetSwitcher = nullptr;
};