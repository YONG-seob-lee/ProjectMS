// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Management/Manager_Both/MS_TableManager.h"


// Log
DECLARE_LOG_CATEGORY_EXTERN(My_Log, Log, All);

#define MS_LOG(InFormat, ...) UE_LOG(My_Log, Log, InFormat, ##__VA_ARGS__)
#define MS_LOG_VERBOSITY(verbosity, msg, ...) UE_LOG(My_Log, verbosity, msg, ##__VA_ARGS__)
#define MS_ERROR(InFormat, ...) UE_LOG(My_Log, Warning, InFormat, ##__VA_ARGS__)

#define MS_CHECK(expr) check(expr)
#define MS_ENSURE(expr) ensure(expr)

#define MS_FUNC_TEXT __FUNCTION__
#define MS_FUNC_STRING FString(__FUNCTION__)


// Object
#define MS_NewObject NewObject

#define MS_DeleteObject(Object) {	 \
MS_CHECK(Object != nullptr);	     	\
Object->ConditionalBeginDestroy();	\
};

template<typename TEnum>
static FString ConvertEnumToString(const FString& aEnumString, TEnum aEnumType)
{
 const UEnum* pEnum = FindFirstObjectSafe<UEnum>(*aEnumString);
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

static FString GetBPNameFromFullPath(const FString& FullPath)
{
 if(FullPath.IsEmpty())
 {
  return FString();
 }

 int32 LastPoint = 0;
 int32 LastSlash = 0;
 constexpr TCHAR Point = '.';
 constexpr TCHAR Slash = '/';
 FullPath.FindLastChar(Point, LastPoint);
 FullPath.FindLastChar(Slash, LastSlash);

 return FullPath.Mid(LastSlash + 1, LastPoint - LastSlash - 1);
}


// Unit
typedef uint32 MS_Handle;
constexpr uint32 InvalidUnitHandle = 0;

UENUM()
enum class EMS_UnitType : int32
{
 Default = 0,
 BasePlayer = 1,
 Storage = 3,
 Vehicle = 4,
 CarSpline = 5,
 DuckSpline = 6,
 CustomerSpline = 7,
 Gate = 8,
 OutsideAI = 9,
 StaffAI = 10,
 CustomerAI = 11,
 Counter = 12
};