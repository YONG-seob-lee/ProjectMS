// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Command/SceneCommand/MS_SceneCommand.h"

/**
 * 
 */
static double ConvertFadeAnimationCurveValue(double aProgressRate, EMS_FadeAnimationCurveType aFadeAnimationCurveType)
{
	if (aFadeAnimationCurveType == EMS_FadeAnimationCurveType::Linear)
	{
		return aProgressRate;
	}
	if (aFadeAnimationCurveType == EMS_FadeAnimationCurveType::EaseIn)
	{
		return -FMath::Sqrt(1 - FMath::Pow(aProgressRate, 2)) + 1;
	}
	if (aFadeAnimationCurveType == EMS_FadeAnimationCurveType::EaseOut)
	{
		return FMath::Sqrt(1 - FMath::Pow(aProgressRate - 1, 2));
	}
	
	return 0.0;
}