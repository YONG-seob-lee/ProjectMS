// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "MS_OrderItemElementData.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FMS_OnClickCountDelegate, int32);
/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_OrderItemElementData : public UObject
{
	GENERATED_BODY()
public:
	FORCEINLINE void SetItemId(int32 aItemId) { ItemId = aItemId; }
	FORCEINLINE void SetImage(UTexture2D* aImage) { ItemImage = aImage; }
	FORCEINLINE void SetItemName(const FString& aItemName) { ItemName = aItemName; }
	FORCEINLINE void SetItemPrice(int32 aPrice) { ItemPrice = aPrice; }
	FORCEINLINE void SetItemCount(int32 aCount) { ItemCount = aCount; }

	FORCEINLINE int32 GetItemId() const { return ItemId; }
	FORCEINLINE UTexture2D* GetImage() const { return ItemImage; }
	FORCEINLINE FString GetItemName() { return ItemName; }
	FORCEINLINE int32 GetItemPrice() const { return ItemPrice; }
	FORCEINLINE int32 GetItemCount() const { return ItemCount; }

	FMS_OnClickCountDelegate OnClickCountDelegate;
private:
	int32 ItemId = 0;
	
	UPROPERTY()
	UTexture2D* ItemImage = nullptr;
	
	FString ItemName = FString();
	int32 ItemPrice = 0;
	int32 ItemCount = 0;
};
