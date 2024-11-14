// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ResourceWidgetCache.h"

#include "..\RowBase\MS_ResourceWidget.h"

void UMS_ResourceWidgetCache::Initialize(TObjectPtr<UMS_TableManager> aMng)
{
	Super::Initialize(aMng);

	TMap<int32, FMS_ResourceWidget*> PrimitiveResourceWidget;
	PrimitiveResourceWidget.Empty();
	
	BuildTable(aMng, EMS_TableDataType::Resource_Widget, PrimitiveResourceWidget);

	for(const auto& ResourceWidgetData : PrimitiveResourceWidget)
	{
		ResourceWidgetDatas.Emplace(ResourceWidgetData.Value->TypeName, ResourceWidgetData.Value);
	}
}

void UMS_ResourceWidgetCache::Finalize()
{
	ResourceWidgetDatas.Empty();

	Super::Finalize();
}

FMS_ResourceWidget* UMS_ResourceWidgetCache::GetResourceWidgetData(const FName& aTypeName)
{
	if(FMS_ResourceWidget** pResourceWidgetData = ResourceWidgetDatas.Find(aTypeName))
	{
		return *pResourceWidgetData;
	}

	return nullptr;
}