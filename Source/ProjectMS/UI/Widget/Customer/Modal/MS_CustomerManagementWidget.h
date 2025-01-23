// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_Define.h"
#include "Widget/MS_Widget.h"
#include "MS_CustomerManagementWidget.generated.h"

UENUM()
enum class EMS_PopulationNumber
{
	One = 0,
	Many = 1
};

UENUM()
enum class EMS_CustomerDetailType
{
	Chatting = 0,
	Behavior = 1,
	Purchase = 2
};
/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_CustomerManagementWidget : public UMS_Widget
{
	GENERATED_BODY()
public:
	static FName GetWidgetName() { return TEXT("CustomerManagement");}

	UFUNCTION()
	virtual void InitWidget(const FName& aTypeName, bool bManaged, bool bAttachToRoot) override;

private:
	void InitManageParameter(EMS_PopulationNumber aPopulationNumber, EMS_CustomerDetailType aDetailType);
	MS_Handle InitComboBox();
	
	void ClearActivateButton() const;

	void OnClickedPersonChatButton();
	void OnClickedPeopleChatButton();
	UFUNCTION()
	void OnSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

	TMap<FString, int32> UnitsName = {};
	
	EMS_PopulationNumber PopulationNumber;
	EMS_CustomerDetailType CustomerDetailType;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_CustomerButton> CPP_PersonChatButton = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<UMS_CustomerButton> CPP_PeopleChatButton = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UComboBoxString> CPP_PersonComboBox = nullptr;
	
	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_WidgetSwitcher> CPP_DetailWidgetSwitcher = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_CustomerDetailWidget> CPP_PersonDetailWidget = nullptr;

	UPROPERTY(Meta = (BindWidget))
	TObjectPtr<class UMS_CustomerDetailWidget> CPP_PeopleDetailWidget = nullptr;
};
