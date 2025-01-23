// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_CustomerManagementWidget.h"

#include "Components/ComboBoxString.h"
#include "LevelScriptActors/MS_MarketLevelScriptActor.h"
#include "Table/Caches/MS_ResourceUnitCacheTable.h"
#include "Widget/Customer/MS_CustomerDetailWidget.h"
#include "Widget/WidgetComponent/MS_WidgetSwitcher.h"

void UMS_CustomerManagementWidget::InitWidget(const FName& aTypeName, bool bManaged, bool bAttachToRoot)
{
	Super::InitWidget(aTypeName, bManaged, bAttachToRoot);

	PopulationNumber = EMS_PopulationNumber::One;
	CustomerDetailType = EMS_CustomerDetailType::Chatting;

	if(CPP_DetailWidgetSwitcher)
	{
		CPP_DetailWidgetSwitcher->SetActiveWidgetIndex(static_cast<int32>(PopulationNumber));
	}

	const MS_Handle FirstPersonUnitHandle = InitComboBox();
	
	if(CPP_PersonDetailWidget)
	{
		CPP_PersonDetailWidget->InitPersonHandle(FirstPersonUnitHandle);
		CPP_PersonDetailWidget->SetType(PopulationNumber, CustomerDetailType);
	}

}

MS_Handle UMS_CustomerManagementWidget::InitComboBox() const
{
	const TObjectPtr<AMS_MarketLevelScriptActor> MarketLevelScriptActor = Cast<AMS_MarketLevelScriptActor>(GetWorld()->GetLevelScriptActor());
	if(!MarketLevelScriptActor)
	{
		MS_Ensure(MarketLevelScriptActor);
		return INDEX_NONE;
	}

	TMap<MS_Handle, bool> UnitsHandleMap;
	MarketLevelScriptActor->GetUnitsHandle(UnitsHandleMap);
	const TObjectPtr<UMS_ResourceUnitCacheTable> UnitTable = Cast<UMS_ResourceUnitCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::ResourceUnit));
	MS_Ensure(UnitTable);

	TArray<MS_Handle> UnitsHandleArray;
	UnitsHandleMap.GenerateKeyArray(UnitsHandleArray);

	TArray<FString> UnitsName;
	UnitTable->GetUnitsName(UnitsHandleArray, UnitsName);

	for(const auto& UnitName : UnitsName)
	{
		CPP_PersonComboBox->AddOption(UnitName);
		CPP_PersonComboBox->SetSelectedIndex(0);
	}

	if(UnitsHandleArray.IsValidIndex(0))
	{
		return UnitsHandleArray[0];
	}

	return INDEX_NONE;
}
