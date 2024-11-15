// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ResourceWidgetCacheTable.h"

#include "..\RowBase\MS_ResourceWidget.h"

void UMS_ResourceWidgetCacheTable::Initialize(TObjectPtr<UMS_TableManager> aMng)
{
	Super::Initialize(aMng);

	TMap<int32, FMS_ResourceWidget*> PrimitiveResourceWidget;
	PrimitiveResourceWidget.Empty();
	
	BuildTable(aMng, EMS_TableDataType::ResourceWidget, PrimitiveResourceWidget);

	for(const auto& ResourceWidgetData : PrimitiveResourceWidget)
	{
		ResourceWidgetDatas.Emplace(ResourceWidgetData.Value->TypeName, ResourceWidgetData.Value);
	}
}

void UMS_ResourceWidgetCacheTable::Finalize()
{
	ResourceWidgetDatas.Empty();

	Super::Finalize();
}

FMS_ResourceWidget* UMS_ResourceWidgetCacheTable::GetResourceWidgetData(const FName& aTypeName)
{
	if(FMS_ResourceWidget** pResourceWidgetData = ResourceWidgetDatas.Find(aTypeName))
	{
		return *pResourceWidgetData;
	}

	return nullptr;
}