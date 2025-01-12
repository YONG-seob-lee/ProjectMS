#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MS_DebugControlStorageItemUI.generated.h"

UCLASS() class PROJECTMS_API UMS_DebugControlStorageItemUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UMS_DebugControlStorageItemUI(const FObjectInitializer& aObjectInitializer);

	virtual void NativeOnInitialized() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;


	UFUNCTION(BlueprintCallable) void AdjustAllStorageItem(const FString& aItemName);
	UFUNCTION() void OnAssignStoragePropertiesButtonClicked();
	UFUNCTION() void OnChangeBoxStaticMeshButtonClicked();
	UFUNCTION() void OnChangeBundleStaticMeshButtonClicked();

	// Component
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget)) TObjectPtr<class UCanvasPanel> RootCanvasPanel = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget)) TObjectPtr<class UTextBlock> StorageTextBlock = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget)) TObjectPtr<class UEditableText> Slot1ItemNameEditableText = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget)) TObjectPtr<class UEditableText> Slot1ItemQuantity = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget)) TObjectPtr<class UEditableText> Slot1ItemCapacity = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget)) TObjectPtr<class UEditableText> Slot2ItemNameEditableText = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget)) TObjectPtr<class UEditableText> Slot2ItemQuantity = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget)) TObjectPtr<class UEditableText> Slot2ItemCapacity = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget)) TObjectPtr<class UEditableText> Slot3ItemNameEditableText = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget)) TObjectPtr<class UEditableText> Slot3ItemQuantity = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget)) TObjectPtr<class UEditableText> Slot3ItemCapacity = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget)) TObjectPtr<class UEditableText> Slot4ItemNameEditableText = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget)) TObjectPtr<class UEditableText> Slot4ItemQuantity = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget)) TObjectPtr<class UEditableText> Slot4ItemCapacity = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget)) TObjectPtr<class UButton> AssignStoragePropertiesButton = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget)) TObjectPtr<class UButton> ChangeBoxStaticMeshButton = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget)) TObjectPtr<class UButton> ChangeBundleStaticMeshButton = nullptr;

	// Property
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TObjectPtr<class AMS_PlayerController> PlayerController = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<UEditableText*> ItemNameEditableTextArray = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<UEditableText*> QuantityEditableTextArray = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<UEditableText*> CapacityEditableTextArray = {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite) TObjectPtr<class AMS_Storage> Storage = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool SlotStaticMeshSwitch = false;
};
