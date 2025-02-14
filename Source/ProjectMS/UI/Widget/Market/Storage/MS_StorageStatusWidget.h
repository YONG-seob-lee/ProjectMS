// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "ContentsUtilities/MS_LevelDefine.h"
#include "ContentsUtilities/MS_ItemDefine.h"
#include "MS_StorageStatusWidget.generated.h"

enum class EMS_ZoneType : uint8;
/**
 * 
 */
DECLARE_DELEGATE_TwoParams(FMS_OnClickRequestSlotDelegate, int32, int32);

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
	void InitializeStorageDatas(EMS_ZoneType aOwnerZoneType, int32 aSlotCount);
	
	void UpdateSlotDatas(const TArray<struct FMS_SlotData>& aSlotDatas);

	
protected:
	EMS_ZoneType OwnerZoneType = EMS_ZoneType::None;

	int32 SlotCount = 0;
	
	TArray<TObjectPtr<class UMS_StorageSlotElementData>> StorageItemElementDatas;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_Button> CPP_ConfirmButton = nullptr;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_TileView> CPP_TileView = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_SelectRequestedItemWidget> CPP_SelectRequestedItemWidget = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_Button> CPP_SkipButton = nullptr;

public:
	// Delegate
	FMS_OnClickRequestSlotDelegate OnClickRequestSlotDelegate;
};