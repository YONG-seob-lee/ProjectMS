#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget/SubEditorUtilityWidget/XSubEditorUtilityWidget.h"
#include "XModeConverterSectionSubEditorUtilityWidget.generated.h"

USTRUCT(BlueprintType) struct FModePreset
{
	GENERATED_BODY()

	UPROPERTY() FString Name = {};
	UPROPERTY() TSoftObjectPtr<UWorld> EditorLevel = {};
	UPROPERTY() TSoftObjectPtr<UWorld> GlobalLevel = {};
	UPROPERTY() TSubclassOf<class UGameInstance> GlobalGameInstance = {};
	UPROPERTY() TSubclassOf<class AGameModeBase> GlobalGameMode = {};
	UPROPERTY() TSoftObjectPtr<UWorld> WorldLevel = {};
	UPROPERTY() TSubclassOf<class AGameModeBase> WorldGameMode = {};
};
USTRUCT(BlueprintType) struct FModePresetPack
{
	GENERATED_BODY()

	UPROPERTY() TArray<FModePreset> ModePresetArray = {};
};

UCLASS() class UXModeConverterSectionSubEditorUtilityWidget : public UXSubEditorUtilityWidget
{
	GENERATED_BODY()

public:
	UXModeConverterSectionSubEditorUtilityWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	UFUNCTION() void OnSaveEditorUtilityButtonClick();
	UFUNCTION() void OnLoadEditorUtilityButtonClick();
	UFUNCTION() void OnEditEditorUtilityButtonClick();
	UFUNCTION() void OnDeleteEditorUtilityButtonClick();
	UFUNCTION() void OnSynchronizeEditorUtilityButtonClick();
	UFUNCTION() void OnClearEditorUtilityButtonClick();
	UFUNCTION() void OnConvertEditorUtilityButtonClick();
	UFUNCTION() void OnConfirmEditorUtilityButtonClick();
	UFUNCTION() void OnCancelEditorUtilityButtonClick();
	UFUNCTION() void OnLevelLoadEnd(const FString& Filename);

	// Property
public:
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UVerticalBox* ContentFrameVerticalBox = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UHorizontalBox* ModePresetFrameHorizontalBox = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UTextBlock* ModePresetLabelTextBlock = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UEditorUtilityComboBoxString* ModePresetEditorUtilityComboBoxString = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UEditorUtilityButton* SaveEditorUtilityButton = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UTextBlock* SaveEditorUtilityButtonLabelTextBlock = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UEditorUtilityButton* LoadEditorUtilityButton = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UTextBlock* LoadEditorUtilityButtonLabelTextBlock = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UEditorUtilityButton* EditEditorUtilityButton = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UTextBlock* EditEditorUtilityButtonLabelTextBlock = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UEditorUtilityButton* DeleteEditorUtilityButton = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UTextBlock* DeleteEditorUtilityButtonLabelTextBlock = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UDetailsView* ParameterDetailsView = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UEditorUtilityButton* SynchronizeEditorUtilityButton = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UTextBlock* SynchronizeEditorUtilityButtonLabelTextBlock = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UEditorUtilityButton* ClearEditorUtilityButton = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UTextBlock* ClearEditorUtilityButtonLabelTextBlock = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UEditorUtilityButton* ConvertEditorUtilityButton = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UTextBlock* ConvertEditorUtilityButtonLabelTextBlock = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UCanvasPanel* ModalFrameCanvasPanel = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UBackgroundBlur* ModalFrameBackgroundBlur = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UCanvasPanel* ModalContentFrameCanvasPanel = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UImage* ModalContentFrameBackgroundImage = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UEditorUtilityEditableTextBox* ModePresetNameEditorUtilityEditableTextBox = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UEditorUtilityButton* ConfirmEditorUtilityButton = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UTextBlock* ConfirmEditorUtilityButtonLabelTextBlock = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UEditorUtilityButton* CancelEditorUtilityButton = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget)) class UTextBlock* CancelEditorUtilityButtonLabelTextBlock = nullptr;

	UPROPERTY() FModePresetPack ModePresetPack = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameter|Global Settings") TSoftObjectPtr<UWorld> EditorLevel = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameter|Global Settings") TSoftObjectPtr<UWorld> GlobalLevel = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameter|Global Settings") TSubclassOf<class UGameInstance> GlobalGameInstance = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameter|Global Settings") TSubclassOf<class AGameModeBase> GlobalGameMode = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameter|World Settings") TSoftObjectPtr<UWorld> WorldLevel = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameter|World Settings") TSubclassOf<class AGameModeBase> WorldGameMode = {};
};