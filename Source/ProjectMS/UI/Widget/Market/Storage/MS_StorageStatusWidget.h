// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_StorageStatusWidget.generated.h"

/**
 * 
 */
DECLARE_DELEGATE_TwoParams(FMS_OnClickShelfSlotDelegate, int32, int32);

UCLASS()
class PROJECTMS_API UMS_StorageStatusWidget : public UMS_Widget
{
	GENERATED_BODY()
	
public:
	static FName GetWidgetName() { return TEXT("StorageStatus"); }
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	void OnClickedConfirmButton();
	void OnClickedStorageSlotButton(int32 aSlotIndex);
	void OnClickedCloseButton();

public:
	void OnChangeSlotDatas(const TArray<struct FMS_SlotData>& aSlotDatas);

	FORCEINLINE void SetOwnerUnit(TWeakObjectPtr<class UMS_UnitBase> aOwnerUnit);

	
protected:
	TWeakObjectPtr<class UMS_UnitBase> OwnerUnit;
	
	TArray<TObjectPtr<class UMS_StorageSlotElementData>> StorageItemElementDatas;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_Button> CPP_ConfirmButton = nullptr;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_TileView> CPP_TileView = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_ShelfStatus> CPP_ShelfStatusWidget = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_Button> CPP_SkipButton = nullptr;

public:
	// Delegate
	FMS_OnClickShelfSlotDelegate OnClickShelfSlotDelegate;
};