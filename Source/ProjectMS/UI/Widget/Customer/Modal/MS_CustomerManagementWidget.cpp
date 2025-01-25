// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_CustomerManagementWidget.h"

#include "Button/MS_CustomerButton.h"
#include "Components/ComboBoxString.h"
#include "LevelScriptActors/MS_MarketLevelScriptActor.h"
#include "Manager_Client/MS_SceneManager.h"
#include "Table/Caches/MS_ResourceUnitCacheTable.h"
#include "Widget/Customer/MS_CustomerDetailWidget.h"
#include "Widget/WidgetComponent/MS_WidgetSwitcher.h"

void UMS_CustomerManagementWidget::InitWidget(const FName& aTypeName, bool bManaged, bool bAttachToRoot)
{
	Super::InitWidget(aTypeName, bManaged, bAttachToRoot);

	InitManageParameter(EMS_PopulationNumber::One, EMS_CustomerDetailType::Chatting);

	ClearActivateButton();
	
	if(CPP_PersonChatButton)
	{
		CPP_PersonChatButton->SetActive(true);
		CPP_PersonChatButton->GetOnClickedDelegate().AddUObject(this, &UMS_CustomerManagementWidget::OnClickedPersonChatButton);
	}
	
	if(CPP_PeopleChatButton)
	{
		CPP_PeopleChatButton->GetOnClickedDelegate().AddUObject(this, &UMS_CustomerManagementWidget::OnClickedPeopleChatButton);
	}

	if(CPP_PersonComboBox)
	{
		CPP_PersonComboBox->OnSelectionChanged.AddDynamic(this, &UMS_CustomerManagementWidget::OnSelectionChanged);
	}

	if(CPP_PersonDetailWidget)
	{
		CPP_PersonDetailWidget->SetOnUpdateCustomerDetailTypeFunc([this](EMS_CustomerDetailType aDetailType)
		{
			CustomerDetailType = aDetailType;
		});
	}

	if(CPP_PeopleDetailWidget)
	{
		CPP_PeopleDetailWidget->SetOnUpdateCustomerDetailTypeFunc([this](EMS_CustomerDetailType aDetailType)
		{
			CustomerDetailType = aDetailType;
		});
	}
}

void UMS_CustomerManagementWidget::InitManageParameter(EMS_PopulationNumber aPopulationNumber, EMS_CustomerDetailType aDetailType)
{
	PopulationNumber = aPopulationNumber;
	CustomerDetailType = aDetailType;

	if(CPP_DetailWidgetSwitcher)
	{
		CPP_DetailWidgetSwitcher->SetActiveWidgetIndex(static_cast<int32>(PopulationNumber));
	}

	
	if(PopulationNumber == EMS_PopulationNumber::One)
	{
		const MS_Handle FirstPersonUnitHandle = InitComboBox();
		CPP_PersonDetailWidget->InitPersonHandle(FirstPersonUnitHandle);
		CPP_PersonDetailWidget->SetType(PopulationNumber, CustomerDetailType);
		CPP_PersonComboBox->SetVisibility(ESlateVisibility::Visible);
	}
	else if(PopulationNumber == EMS_PopulationNumber::Many)
	{
		CPP_PeopleDetailWidget->SetType(PopulationNumber, CustomerDetailType);
		CPP_PersonComboBox->SetVisibility(ESlateVisibility::Collapsed);
	}
}

MS_Handle UMS_CustomerManagementWidget::InitComboBox()
{
	const TObjectPtr<AMS_MarketLevelScriptActor> MarketLevelScriptActor = Cast<AMS_MarketLevelScriptActor>(gSceneMng.GetCurrentLevelScriptActor());
	if(!MarketLevelScriptActor)
	{
		MS_ENSURE(MarketLevelScriptActor);
		return INDEX_NONE;
	}

	TMap<MS_Handle, bool> UnitsHandleMap;
	MarketLevelScriptActor->GetUnitsHandle(UnitsHandleMap);
	const TObjectPtr<UMS_ResourceUnitCacheTable> UnitTable = Cast<UMS_ResourceUnitCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::ResourceUnit));
	MS_ENSURE(UnitTable);

	TArray<MS_Handle> UnitsHandleArray;
	UnitsHandleMap.GenerateKeyArray(UnitsHandleArray);
	
	UnitTable->GetUnitsName(UnitsHandleArray, UnitsName);

	CPP_PersonComboBox->ClearOptions();
	
	for(const auto& UnitName : UnitsName)
	{
		CPP_PersonComboBox->AddOption(UnitName.Key);
		CPP_PersonComboBox->SetSelectedIndex(0);
	}

	if(UnitsHandleArray.IsValidIndex(0))
	{
		return UnitsHandleArray[0];
	}

	return INDEX_NONE;
}

void UMS_CustomerManagementWidget::ClearActivateButton() const
{
	CPP_PersonChatButton->SetActive(false);
	CPP_PeopleChatButton->SetActive(false);
}

void UMS_CustomerManagementWidget::OnClickedPersonChatButton()
{
	ClearActivateButton();
	CPP_PersonChatButton->SetActive(true);
	InitManageParameter(EMS_PopulationNumber::One, CustomerDetailType);
}

void UMS_CustomerManagementWidget::OnClickedPeopleChatButton()
{
	ClearActivateButton();
	CPP_PeopleChatButton->SetActive(true);
	InitManageParameter(EMS_PopulationNumber::Many, CustomerDetailType);
}

void UMS_CustomerManagementWidget::OnSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	if(const int32* UnitHandle = UnitsName.Find(SelectedItem))
	{
		CPP_PersonDetailWidget->InitPersonHandle(*UnitHandle);
		CPP_PersonDetailWidget->SetType(PopulationNumber, CustomerDetailType);
		CPP_PersonComboBox->SetVisibility(ESlateVisibility::Visible);	
	}
}
