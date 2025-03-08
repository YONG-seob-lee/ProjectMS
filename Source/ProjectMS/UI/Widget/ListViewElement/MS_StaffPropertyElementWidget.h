// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "ContentsUtilities/MS_AIDefine.h"
#include "Widget/MS_Widget.h"
#include "MS_StaffPropertyElementWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_StaffPropertyElementWidget : public UMS_Widget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnListItemObjectSet(UObject* aListItemObject) override;
	virtual void NativeOnItemSelectionChanged(bool bIsSelected) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

private:
	UFUNCTION()
	void OnSelectChanged(FString SelectedItem, ESelectInfo::Type SelectionType);
	
	FString GetUIIssueName(int32 aUIIssueType);
	
	int32 StaffId = INDEX_NONE;

	int32 StaffIdTag = INDEX_NONE;

	EMS_StaffUIPriorityType StaffUIPriorityType = EMS_StaffUIPriorityType::PaymentFirst;
	
	int32 WorkDay = 0;
	
	TMap<int32, FString> SelectItems;
	
	UPROPERTY(meta= (BindWidget))
	TObjectPtr<class UImage> CPP_PortraitImage = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UComboBoxString> CPP_StaffIssueBox = nullptr;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_Name = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_HP = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_Condition = nullptr;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_Feeling = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UTextBlock> CPP_ExpirationDate = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UCanvasPanel> CPP_BlurPanel = nullptr;
};
