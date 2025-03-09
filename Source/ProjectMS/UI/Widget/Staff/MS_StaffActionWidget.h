// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ContentsUtilities/MS_AIDefine.h"
#include "Widget/MS_Widget.h"
#include "MS_StaffActionWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_StaffActionWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	static FName GetWidgetName() { return TEXT("StaffAction"); }
	virtual void InitWidget(const FName& aTypeName, bool bManaged, bool bAttachToRoot) override;
	virtual void InitStaffActionWidget(TWeakObjectPtr<class UMS_StaffAIUnit> aOwnerUnit);

	virtual void SynchronizeProperties() override;
	
private:
	void InitStaffActionBox();
	FString GetUIIssueName(int32 aUIIssueType) const;
	
	void OnClickedCancelButton();
	UFUNCTION()
	void OnSelectChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

	TMap<int32, FString> SelectItems; 
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UComboBoxString> CPP_StaffIssueBox = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_Button> CPP_Button = nullptr;

	UPROPERTY()
	TWeakObjectPtr<class UMS_StaffAIUnit> OwnerUnit;
};
