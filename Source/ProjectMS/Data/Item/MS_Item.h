// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "MS_Item.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_Item : public UObject
{
	GENERATED_BODY()
public:
	void Initialize(int32 aItemId);

	UTexture2D* GetItemTexture() const;
private:
	int32 ItemId = INDEX_NONE;
};
