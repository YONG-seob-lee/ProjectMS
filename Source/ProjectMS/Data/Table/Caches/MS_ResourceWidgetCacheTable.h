// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectMS/Data/Table/MS_CacheTable.h"
#include "MS_ResourceWidgetCacheTable.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_ResourceWidgetCacheTable : public UMS_CacheTable
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(TObjectPtr<UMS_TableManager> aMng) override;
	virtual void Finalize() override;
	
	struct FMS_ResourceWidget* GetResourceWidgetData(const FName& aTypeName);
	
private:
	TMap<FName, FMS_ResourceWidget*> ResourceWidgetDatas;
};
