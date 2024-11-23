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
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UVerticalBox* ContentFrameVerticalBox = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UHorizontalBox* ControllerFrameHorizontalBox = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UEditorUtilityButton* RunEditorUtilityButton = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UTextBlock* RunEditorUtilityButtonLabelTextBlock = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UEditorUtilityButton* ClearEditorUtilityButton = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UTextBlock* ClearEditorUtilityButtonLabelTextBlock = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UEditorUtilityButton* ImportEditorUtilityButton = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UTextBlock* ImportEditorUtilityButtonLabelTextBlock = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UEditorUtilityButton* ExportEditorUtilityButton = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UTextBlock* ExportEditorUtilityButtonLabelTextBlock = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class USizeBox* CodeFrameSizeBox = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UEditorUtilityMultiLineEditableTextBox* CodeEditorUtilityMultiLineEditableTextBox = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class USizeBox* ConsoleFrameSizeBox = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UEditorUtilityMultiLineEditableTextBox* ConsoleEditorUtilityMultiLineEditableTextBox = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UOverlay* SnippetFrameOverlay = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UImage* SnippetFrameBackgroundImage = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UUniformGridPanel* SnippetUniformGridPanel = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UDetailsView* ParameterDetailsView = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameter") TArray<TSoftObjectPtr<AActor>> TargetArray = {};
};