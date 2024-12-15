// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Table/MS_CacheTable.h"
#include "Table/RowBase/MS_Common.h"
#include "MS_CommonCacheTable.generated.h"

namespace CommonContents
{
	const FString POINTER_HOLD_DELAY = TEXT("POINTER_HOLD_DELAY");
	const FString POINTER_CLICK_DELAY = TEXT("POINTER_CLICK_DELAY");
	const FString POINTER_DOUBLE_CLICK_DELAY = TEXT("POINTER_DOUBLE_CLICK_DELAY");
	const FString POINTER_DOUBLE_CLICK_POSITION_TOLERANCE = TEXT("POINTER_DOUBLE_CLICK_POSITION_TOLERANCE");
}

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_CommonCacheTable : public UMS_CacheTable
{
	GENERATED_BODY()
public:
	virtual void Initialize(TObjectPtr<UMS_TableManager> aMng) override;
	virtual void Finalize() override;

	int32 GetParameter01(const FString& aContents);
	float GetParameter02(const FString& aContents);

private:
	TMap<FString, FMS_Common*> CommonDatas;
};
