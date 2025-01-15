// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "MS_StockItemElementData.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_StockItemElementData : public UObject
{
	GENERATED_BODY()
public:
	
	FORCEINLINE void SetImage(UTexture2D* aImage) { ItemImage = aImage; }
	FORCEINLINE void SetItemName(const FString& aItemName) { ItemName = aItemName; }
	FORCEINLINE void SetItemCount(int32 aCount) { ItemCount = aCount; }
	
	FORCEINLINE UTexture2D* GetImage() const { return ItemImage; }
	FORCEINLINE FString GetItemName() { return ItemName; }
	FORCEINLINE int32 GetItemCount() const { return ItemCount; }

private:
	UPROPERTY()
	UTexture2D* ItemImage = nullptr;
	
	FString ItemName = FString();
	int32 ItemCount = 0;
};
