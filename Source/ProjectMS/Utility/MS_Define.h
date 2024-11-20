// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Command/SceneCommand/MS_SceneCommand.h"
#include "Management/Public/MS_TableManager.h"
//#include "MS_Define.generated.h"

/**
 * 
 */


typedef int32 MS_Handle;
constexpr int32 InvalidUnitHandle = 0;

DECLARE_LOG_CATEGORY_EXTERN(My_Log, Log, All);

#define MS_LOG(InFormat, ...) UE_LOG(My_Log, Log, InFormat, ##__VA_ARGS__)
#define MS_LOG_Verbosity(verbosity, msg, ...) UE_LOG(My_Log, verbosity, msg, ##__VA_ARGS__)

#define MS_CHECK(expr) check(expr)

// Object
#define MS_NewObject NewObject

#define MS_DeleteObject(Object) {	 \
MS_CHECK(Object != nullptr);	     	\
Object->ConditionalBeginDestroy();	\
};

template<typename TEnum>
static FString ConvertEnumToString(const FString& aEnumString, TEnum aEnumType)
{
 const UEnum* pEnum = FindObject<UEnum>(ANY_PACKAGE, *aEnumString);
 if (!pEnum)
 {
  return FString("");
 }

 const int32 Index = pEnum->GetIndexByValue(static_cast<int32>(aEnumType));
 return pEnum->GetNameStringByIndex(Index);
}


static TObjectPtr<UDataTable> LoadTableObjectFromFile(const FString& aResourcePath, const FString& aTableName, const FMS_LoadResourceDelegate& aDelegate)
{
 const TObjectPtr<UDataTable> ResultObject = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *aResourcePath, *aResourcePath, LOAD_None, nullptr));

 if(aDelegate.IsBound())
 {
  aDelegate.Execute(aTableName, ResultObject);
 }
	
 return ResultObject;
}

static TObjectPtr<UObject> LoadObjectFromFile(FStreamableManager& aAssetLoader, const FString& aResourcePath, const FMS_LoadResourceDelegate& aDelegate = nullptr, const FString& aSubName = TEXT("SubName"), int32 aIndex = 0, bool aSubBool = false)
{
 const FSoftObjectPath Reference = FSoftObjectPath(aResourcePath);
	
 UObject* ResultObject = aAssetLoader.LoadSynchronous(Reference);
 if(aDelegate.IsBound())
 {
  aDelegate.Execute(aResourcePath, ResultObject);
 }
 return ResultObject;
}

// Widget

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

#define CREATE_SCENE_COMMAND(CommandName) \
TObjectPtr<class UMS_SceneCommand> CommandName = MS_NewObject<UMS_SceneCommand>(); \
CommandName->SetCreateFrom(__FILE__, __LINE__);