// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TileView.h"
#include "MS_TileView.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_TileView : public UTileView
{
	GENERATED_BODY()
public:
	void SetElements(const TArray<TObjectPtr<UObject>>& aListItems);
};
