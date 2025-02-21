// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "MS_ConstructItemElement.generated.h"

DECLARE_MULTICAST_DELEGATE(FMS_OnClickConstructItem)
/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_ConstructItemElement : public UObject
{
	GENERATED_BODY()
public:
	FORCEINLINE void SetImage(UTexture2D* aImage) { Image = aImage; }
	FORCEINLINE void SetElementName(const FString& aElementName) { ElementName = aElementName; }
	FORCEINLINE void SetZoneType(int32 aZoneType) { ZoneType = aZoneType; }
	FORCEINLINE void SetItemId(int32 aId) { ItemId = aId; }
	
	FORCEINLINE UTexture2D* GetImage() const { return Image; }
	FORCEINLINE FString GetElementName() { return ElementName; }
	FORCEINLINE int32 GetItemId() const { return ItemId; }
	FORCEINLINE int32 GetZoneType() const { return ZoneType; }

	FMS_OnClickConstructItem OnClickConstructItem;
private:
	UPROPERTY()
	UTexture2D* Image = nullptr;
	FString ElementName = FString();
	int32 ItemId = 0;
	int32 ZoneType = 0;
};
