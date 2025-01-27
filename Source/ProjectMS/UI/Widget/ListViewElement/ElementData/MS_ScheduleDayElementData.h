// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MS_ScheduleDayElementData.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_ScheduleDayElementData : public UObject
{
	GENERATED_BODY()
public:
	FORCEINLINE void SetDays(int32 aDay) { Day = aDay; }
	FORCEINLINE void SetColor(FLinearColor aColor) { Color = aColor; }
	
	FORCEINLINE int32 GetDays() const { return Day; }
	FORCEINLINE FLinearColor GetColor() const { return Color; }

private:
	int32 Day = 0;
	FLinearColor Color = FLinearColor::White;
};
