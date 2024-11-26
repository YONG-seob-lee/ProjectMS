#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget/SubEditorUtilityWidget/XSubEditorUtilityWidget.h"
#include "XScriptExecutorSectionSubEditorUtilityWidget.generated.h"

UCLASS() class UXScriptExecutorSectionSubEditorUtilityWidget : public UXSubEditorUtilityWidget
{
	GENERATED_BODY()

public:
	UXScriptExecutorSectionSubEditorUtilityWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	// Property
public:
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UVerticalBox* ContentFrameVerticalBox = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UHorizontalBox* ControllerFrameHorizontalBox = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UEditorUtilityButton* RunEditorUtilityButton = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UTextBlock* RunEditorUtilityButtonLabelTextBlock = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UEditorUtilityButton* ClearEditorUtilityButton = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UTextBlock* ClearEditorUtilityButtonLabelTextBlock = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UEditorUtilityButton* ImportEditorUtilityButton = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UTextBlock* ImportEditorUtilityButtonLabelTextBlock = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UEditorUtilityButton* ExportEditorUtilityButton = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UTextBlock* ExportEditorUtilityButtonLabelTextBlock = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class USizeBox* CodeFrameSizeBox = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UEditorUtilityMultiLineEditableTextBox* CodeEditorUtilityMultiLineEditableTextBox = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class USizeBox* ConsoleFrameSizeBox = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UEditorUtilityMultiLineEditableTextBox* ConsoleEditorUtilityMultiLineEditableTextBox = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UOverlay* SnippetFrameOverlay = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UImage* SnippetFrameBackgroundImage = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UUniformGridPanel* SnippetUniformGridPanel = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UDetailsView* ParameterDetailsView = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameter") TArray<TSoftObjectPtr<AActor>> TargetArray = {};
};