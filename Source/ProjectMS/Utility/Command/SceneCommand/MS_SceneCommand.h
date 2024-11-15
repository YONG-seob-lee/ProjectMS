// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MS_SceneCommand.generated.h"

UENUM()
enum class EMS_LevelType
{
	None = 0,
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
enum class EMS_LoadingPageType : uint8
{
	None = 0,
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
	FORCEINLINE void SetTransitionStyle(EMS_TransitionStyle aStyle) { TransitionStyle = aStyle; }
	FORCEINLINE void SetLoadingPageType(EMS_LoadingPageType aType) { LoadingPageType = aType; }
	FORCEINLINE void SetLoadingWidget(const TSubclassOf<class UMS_Widget>& aLoadingWidget) { LoadingWidget = aLoadingWidget; }
	FORCEINLINE void SetNextWidget(const TSubclassOf<UMS_Widget>& aNextWidget) { NextWidget = aNextWidget; }
	
	FORCEINLINE EMS_LevelType GetLevelType() const { return LevelType; }
	FORCEINLINE EMS_TransitionStyle GetTransitionStyle() const { return TransitionStyle; }
	FORCEINLINE EMS_LoadingPageType GetLoadingPageType() const { return LoadingPageType; }
	FORCEINLINE TSubclassOf<UMS_Widget> GetLoadingWidget() { return LoadingWidget; }
	FORCEINLINE TSubclassOf<UMS_Widget> GetNextWidget() { return NextWidget; }

	void SetCreateFrom(const ANSICHAR* File, const int32 Line);
	
private:
	TSubclassOf<UMS_Widget> LoadingWidget = nullptr;
	TSubclassOf<UMS_Widget> NextWidget = nullptr;
	
	EMS_LevelType LevelType = EMS_LevelType::None;
	EMS_TransitionStyle TransitionStyle = EMS_TransitionStyle::Undefined;
	EMS_LoadingPageType LoadingPageType = EMS_LoadingPageType::None;

	FString CreateFileLine = FString();
};
