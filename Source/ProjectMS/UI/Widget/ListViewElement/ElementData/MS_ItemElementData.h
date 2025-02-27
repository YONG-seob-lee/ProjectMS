// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_ItemElementData.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_ItemElementData : public UObject
{
	GENERATED_BODY()
public:
	FORCEINLINE void SetImage(UTexture2D* aImage) { Image = aImage; }
	FORCEINLINE void SetElementName(const FString& aElementName) { ElementName = aElementName; }
	FORCEINLINE void SetItemCount(int32 aItemCount) { ItemCount = aItemCount; }
	FORCEINLINE void ShowItemName(bool bShow) { bShowItemName = bShow; }
	FORCEINLINE void ShowItemCount(bool bShow) { bShowItemCount = bShow; }
	
	FORCEINLINE UTexture2D* GetImage() const { return Image; }
	FORCEINLINE FString GetElementName() { return ElementName; }
	FORCEINLINE int32 GetItemCount() const { return ItemCount; }
	FORCEINLINE bool IsShowItemName() const { return bShowItemName; }
	FORCEINLINE bool IsShowItemCount() const { return bShowItemCount; }

private:
	UPROPERTY()
	UTexture2D* Image = nullptr;
	FString ElementName = FString();

	int32 ItemCount = 0;
	bool bShowItemName = true;
	bool bShowItemCount = false;
};
