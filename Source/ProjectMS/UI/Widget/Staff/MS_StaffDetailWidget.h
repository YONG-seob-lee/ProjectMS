// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_StaffDetailWidget.generated.h"

UENUM()
enum class EMS_AbilityType : uint8
{
	Undefined = 0,
	Work,
	Endurance,
	Diligence,
	Kindness,
	Plannedness,
};
/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_StaffDetailWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	static FName GetWidgetName() { return TEXT("StaffDetail"); }
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	void SetDetail(int32 aStaffId);
	void ShowButtonPanel(bool bShow) const;
	
private:
	void OnClickedHireButton();
	void OnClickedReconsiderButton();
	
	FString GetAbilityName(int32 aAbilityType);

	int32 StaffId = INDEX_NONE;
	
	UPROPERTY()
	TArray<class UMS_AbilityElementData*> AbilityElementDatas;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_StaffProfileElementWidget> CPP_ProfileWidget = nullptr;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_ListView> CPP_AbilityListView = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UCanvasPanel> CPP_ButtonPanel = nullptr;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_Button> CPP_HireButton = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_Button> CPP_ReconsiderButton = nullptr;
};
