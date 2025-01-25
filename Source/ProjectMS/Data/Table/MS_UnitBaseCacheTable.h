// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_CacheTable.h"
#include "MS_UnitBaseCacheTable.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_UnitBaseCacheTable : public UMS_CacheTable
{
	GENERATED_BODY()

public:
	virtual int32 GetUnitBaseBPIndex(int32 aId) const
	{
		MS_LOG_VERBOSITY(Error, TEXT("[%s] Please override this fuction in your cache table"), *MS_FUNC_STRING);
		MS_ENSURE(false);
		
		return INDEX_NONE;
	}
};
