#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget/SubEditorUtilityWidget/XSubEditorUtilityWidget.h"
#include "XDataRefresherSectionSubEditorUtilityWidget.generated.h"

USTRUCT(BlueprintType) struct FTypeMeta
{
	GENERATED_BODY()

	UPROPERTY() FString EditorTypeName = {};
	UPROPERTY() FString CppTypeName = {};
	UPROPERTY() FLinearColor TypeColor = {};
};
USTRUCT(BlueprintType) struct FTypeMetaPack
{
	GENERATED_BODY()

	UPROPERTY() TArray<FTypeMeta> TypeMetaArray = {};
};

UCLASS() class UXDataRefresherSectionSubEditorUtilityWidget : public UXSubEditorUtilityWidget
{
	GENERATED_BODY()

public:
	UXDataRefresherSectionSubEditorUtilityWidget(const FObjectInitializer& ObjectInitializer);
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	UFUNCTION() void OnExcelFileEditorUtilityComboBoxStringSelect(FString SelectedItem, ESelectInfo::Type SelectionType);
	UFUNCTION() void OnExcelSheetEditorUtilityComboBoxStringSelect(FString SelectedItem, ESelectInfo::Type SelectionType);
	UFUNCTION() void OnBrowsePathEditorUtilityButtonClick();
	UFUNCTION() void OnSearchFileEditorUtilityButtonClick();
	UFUNCTION() void OnRevealRootPathFolderEditorUtilityButtonClick();
	UFUNCTION() void OnRevealExcelFileFolderEditorUtilityButtonClick();
	UFUNCTION() void OnRevealDataTableFileFolderEditorUtilityButtonClick();
	UFUNCTION() void OnRevealHeaderFileFolderEditorUtilityButtonClick();
	UFUNCTION() void OnAssignDataTableEditorUtilityButtonClick();
	UFUNCTION() void OnAssignHeaderEditorUtilityButtonClick();
	UFUNCTION() void OnAssignAllEditorUtilityButtonClick();
	UFUNCTION() void OnGenerateCSVFileEditorUtilityButtonClick();
	UFUNCTION() void OnCaptureAllDataEditorUtilityButtonClick();
	UFUNCTION() void OnDataTableValueChange();
	void RecordLog(const FString& aMessage);
	void FillDataFieldToHorizontalBox(class UHorizontalBox* aHorizontalBox, const TArray<FString>& aDataTypeNameArray, const TArray<FString>& aDataNameArray);
	void UpdateExcelDataField();
	void BackupFile(const FString& aFilePath);

	// Property
public:
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UVerticalBox* ContentFrameVerticalBox = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UHorizontalBox* Browser1FrameHorizontalBox = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UTextBlock* ExcelFileLabelTextBlock = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UEditorUtilityComboBoxString* ExcelFileEditorUtilityComboBoxString = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UTextBlock* ExcelSheetLabelTextBlock = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UEditorUtilityComboBoxString* ExcelSheetEditorUtilityComboBoxString = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UEditorUtilityEditableTextBox* RootPathEditorUtilityEditableTextBox = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UEditorUtilityButton* BrowsePathEditorUtilityButton = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UTextBlock* BrowsePathEditorUtilityButtonLabelTextBlock = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UEditorUtilityButton* SearchFileEditorUtilityButton = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UTextBlock* SearchFileEditorUtilityButtonLabelTextBlock = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UHorizontalBox* Browser2FrameHorizontalBox = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UEditorUtilityButton* RevealRootPathFolderEditorUtilityButton = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UTextBlock* RevealRootPathFolderEditorUtilityButtonLabelTextBlock = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UEditorUtilityButton* RevealExcelFileFolderEditorUtilityButton = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UTextBlock* RevealExcelFileFolderEditorUtilityButtonLabelTextBlock = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UEditorUtilityButton* RevealDataTableFileFolderEditorUtilityButton = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UTextBlock* RevealDataTableFileFolderEditorUtilityButtonLabelTextBlock = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UEditorUtilityButton* RevealHeaderFileFolderEditorUtilityButton = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UTextBlock* RevealHeaderFileFolderEditorUtilityButtonLabelTextBlock = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UDetailsView* ParameterDetailsView = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UHorizontalBox* ControllerFrameHorizontalBox = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UEditorUtilityButton* AssignDataTableEditorUtilityButton = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UTextBlock* AssignDataTableEditorUtilityButtonLabelTextBlock = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UEditorUtilityButton* AssignHeaderEditorUtilityButton = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UTextBlock* AssignHeaderEditorUtilityButtonLabelTextBlock = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UEditorUtilityButton* AssignAllEditorUtilityButton = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UTextBlock* AssignAllEditorUtilityButtonLabelTextBlock = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UEditorUtilityButton* GenerateCSVFileEditorUtilityButton = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UTextBlock* GenerateCSVFileEditorUtilityButtonLabelTextBlock = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UEditorUtilityButton* CaptureAllDataEditorUtilityButton = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UTextBlock* CaptureAllDataEditorUtilityButtonLabelTextBlock = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UOverlay* ExcelDataFieldFrameOverlay = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UImage* ExcelDataFieldFrameBackgroundImage = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UTextBlock* ExcelDataFieldLabelTextBlock = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UEditorUtilityScrollBox* ExcelDataFieldFrameEditorUtilityScrollBox = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UHorizontalBox* ExcelDataFieldFrameHorizontalBox = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UOverlay* HeaderDataFieldFrameOverlay = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UImage* HeaderDataFieldFrameBackgroundImage = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UTextBlock* HeaderDataFieldLabelTextBlock = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UEditorUtilityScrollBox* HeaderDataFieldFrameEditorUtilityScrollBox = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UHorizontalBox* HeaderDataFieldFrameHorizontalBox = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class USizeBox* LogFrameSizeBox = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UEditorUtilityScrollBox* LogFrameEditorUtilityScrollBox = nullptr;
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "WidgetComponent") class UEditorUtilityMultiLineEditableTextBox* LogEditorUtilityMultiLineEditableTextBox = nullptr;

	TSubclassOf<class UXDataFieldEditorUtilityWidget> DataFieldEditorUtilityWidgetClass = {};
	UPROPERTY() FTypeMetaPack TypeMetaPack = {};
	long long ExcelFileModificationTime = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameter") TSoftObjectPtr<class UDataTable> DataTable = {};
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Parameter") FString Header = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameter") bool BackupFlag = false;
};