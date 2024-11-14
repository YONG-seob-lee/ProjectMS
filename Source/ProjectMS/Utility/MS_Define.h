// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Management/MS_TableManager.h"
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
static FString ConvertEnumToString(const FString& EnumString, TEnum EnumType)
{
 const UEnum* pEnum = FindObject<UEnum>(ANY_PACKAGE, *EnumString);
 if (!pEnum)
 {
  return FString("");
 }

 const int32 Index = pEnum->GetIndexByValue(static_cast<int32>(EnumType));
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