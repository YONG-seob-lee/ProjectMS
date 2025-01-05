// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager_Client/MS_ItemManager.h"

#include "MS_ConstructCategoryElementData.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_ConstructCategoryElementData : public UObject
{
	GENERATED_BODY()
public:
	FORCEINLINE void SetStorageType(int32 aStorageType) { StorageType = aStorageType; }
	FORCEINLINE int32 GetStorageType() const { return StorageType; }

private:
	int32 StorageType = 0;
};
