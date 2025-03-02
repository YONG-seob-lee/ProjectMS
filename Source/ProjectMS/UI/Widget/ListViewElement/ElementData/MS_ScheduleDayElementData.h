// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ContentsUtilities/MS_GameProcessDefine.h"
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
	FORCEINLINE void SetDate(FMS_GameDate aDay) { Date = aDay; }
	FORCEINLINE void SetColor(FLinearColor aColor) { Color = aColor; }
	
	FORCEINLINE FMS_GameDate GetDate() const { return Date; }
	FORCEINLINE FLinearColor GetColor() const { return Color; }

private:
	FMS_GameDate Date = FMS_GameDate();
	FLinearColor Color = FLinearColor::White;
};
