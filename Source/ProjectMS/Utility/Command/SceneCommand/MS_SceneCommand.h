// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MS_SceneCommand.generated.h"


UENUM()
enum class EMS_LevelType
{
	None = 0,
	Persistence = 1,
	Practice_01 = 2,
	Practice_02 = 3,
	Lobby = 4,
};

UENUM()
enum class EMS_TransitionStyle : uint8
{
	Undefined = 0,
	FadeFromLeavingPage,
	FadeFromEnteringPage,
	FloatFromTop,
	FloatFromBottom,
	FloatFromLeft,
	FloatFromRight
};

UENUM()
enum class EMS_LoadingWidgetType : uint8
{
	Default = 0,
};

UENUM()
enum class EMS_FadeAnimationCurveType : uint8
{
	Undefined,
	Linear,
	EaseIn,
	EaseOut
};
/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_SceneCommand : public UObject
{
	GENERATED_BODY()
public:
	FORCEINLINE void SetLevelType(EMS_LevelType aType) { LevelType = aType; }
	FORCEINLINE void SetPreviousLevelType(EMS_LevelType aType) { PreviousLevelType = aType; }
	FORCEINLINE void SetFadeOutTransitionType(EMS_TransitionStyle aStyle) { FadeOutTransitionStyle = aStyle; }
	FORCEINLINE void SetFadeInTransitionType(EMS_TransitionStyle aStyle) { FadeInTransitionStyle = aStyle; }
	FORCEINLINE void SetLoadingWidgetType(EMS_LoadingWidgetType aType) { LoadingWidgetType = aType; }
	// If do not Reload Level. Use this Function.
	FORCEINLINE void SetNextWidget(const TSubclassOf<class UMS_Widget>& aNextWidget) { NextWidget = aNextWidget; }
	FORCEINLINE void SetFadeAnimationType(EMS_FadeAnimationCurveType aFadeAnimationCurveType) { FadeAnimationCurveType = aFadeAnimationCurveType; } 
	
	FORCEINLINE EMS_LevelType GetLevelType() const { return LevelType; }
	FORCEINLINE EMS_LevelType GetPreviousLevelType() const { return PreviousLevelType; }
	FORCEINLINE EMS_TransitionStyle GetFadeOutTransitionStyle() const { return FadeOutTransitionStyle; }
	FORCEINLINE EMS_TransitionStyle GetFadeInTransitionStyle() const { return FadeInTransitionStyle; }
	FORCEINLINE EMS_LoadingWidgetType GetLoadingPageType() const { return LoadingWidgetType; }
	FORCEINLINE TSubclassOf<class UMS_Widget> GetLoadingWidget() { return LoadingWidget; }
	FORCEINLINE TSubclassOf<class UMS_Widget> GetNextWidget() { return NextWidget; }
	FORCEINLINE EMS_FadeAnimationCurveType GetFadeAnimationCurveType() const { return FadeAnimationCurveType; }
	void SetCreateFrom(const ANSICHAR* File, const int32 Line);

private:
	TSubclassOf<UMS_Widget> LoadingWidget = nullptr;
	TSubclassOf<UMS_Widget> NextWidget = nullptr;

	EMS_LevelType LevelType = EMS_LevelType::None;
	EMS_LevelType PreviousLevelType = EMS_LevelType::None;
	EMS_TransitionStyle FadeOutTransitionStyle = EMS_TransitionStyle::Undefined;
	EMS_TransitionStyle FadeInTransitionStyle = EMS_TransitionStyle::Undefined;
	EMS_LoadingWidgetType LoadingWidgetType = EMS_LoadingWidgetType::Default;
	EMS_FadeAnimationCurveType FadeAnimationCurveType = EMS_FadeAnimationCurveType::Undefined; 

	FString CreateFileLine = FString();
};
