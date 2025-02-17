// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MS_SceneCommand.generated.h"

DECLARE_MULTICAST_DELEGATE(FMS_FadeEventDelegate);

UENUM()
enum class EMS_LevelType
{
	None = 0,
	PersistenceLevel = 1,
	AccountLevel = 2,
	LobbyLevel = 3,
	Stage01 = 4,
	Stage02 = 5,
	Stage03 = 6,
	MarketLevel = 7,
	
	PracticeLevel_01 = 1000,
	PracticeLevel_02 = 1001,
};

UENUM()
enum class EMS_TransitionStyle : uint8
{
	Undefined = 0,
	GradationIn,
	GradationOut,
	FloatFromTop,
	FloatFromBottom,
	FloatFromLeft,
	FloatFromRight
};

UENUM()
enum class EMS_LoadingWidgetType : uint8
{
	Undefined = 0,
	Default = 1,
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
	FORCEINLINE void SetNextWidget(const FName& aWidgetName) { WidgetName = aWidgetName; }
	FORCEINLINE void SetFadeAnimationType(EMS_FadeAnimationCurveType aFadeAnimationCurveType) { FadeAnimationCurveType = aFadeAnimationCurveType; }
	FORCEINLINE void SetAllowInteractActor(bool bAllow) { bAllowInteractActor = bAllow;}
	
	FORCEINLINE EMS_LevelType GetLevelType() const { return LevelType; }
	FORCEINLINE EMS_LevelType GetPreviousLevelType() const { return PreviousLevelType; }
	FORCEINLINE EMS_TransitionStyle GetFadeOutTransitionStyle() const { return FadeOutTransitionStyle; }
	FORCEINLINE EMS_TransitionStyle GetFadeInTransitionStyle() const { return FadeInTransitionStyle; }
	FORCEINLINE EMS_LoadingWidgetType GetLoadingPageType() const { return LoadingWidgetType; }
	FORCEINLINE TSubclassOf<class UMS_Widget> GetLoadingWidget() { return LoadingWidget; }
	FORCEINLINE FName GetNextWidgetName() const { return WidgetName; }
	FORCEINLINE EMS_FadeAnimationCurveType GetFadeAnimationCurveType() const { return FadeAnimationCurveType; }
	FORCEINLINE bool IsAllowInteractActor() const { return bAllowInteractActor; }
	void SetCreateFrom(const ANSICHAR* File, const int32 Line);
	
	FMS_FadeEventDelegate OnFadeEventDelegate;
	TFunction<void()> OnFadeInFinishedCallback;
private:
	TSubclassOf<UMS_Widget> LoadingWidget = nullptr;
	FName WidgetName = FName();

	EMS_LevelType LevelType = EMS_LevelType::None;
	EMS_LevelType PreviousLevelType = EMS_LevelType::None;
	EMS_TransitionStyle FadeOutTransitionStyle = EMS_TransitionStyle::Undefined;
	EMS_TransitionStyle FadeInTransitionStyle = EMS_TransitionStyle::Undefined;
	EMS_LoadingWidgetType LoadingWidgetType = EMS_LoadingWidgetType::Default;
	EMS_FadeAnimationCurveType FadeAnimationCurveType = EMS_FadeAnimationCurveType::Undefined; 

	bool bAllowInteractActor = true;
	
	FString CreateFileLine = FString();
};
