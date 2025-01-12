// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/MS_Widget.h"
#include "MS_ItemElementData.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_ItemElementData : public UMS_Widget
{
	GENERATED_BODY()
public:
	FORCEINLINE void SetImage(UTexture2D* aImage) { Image = aImage; }
	FORCEINLINE void SetElementName(const FString& aElementName) { ElementName = aElementName; }
	FORCEINLINE UTexture2D* GetImage() const { return Image; }
	FORCEINLINE FString GetElementName() { return ElementName; }
	
private:
	UPROPERTY()
	UTexture2D* Image = nullptr;
	FString ElementName = FString();  
};
