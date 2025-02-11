// Fill out your copyright notice in the Description page of Project Settings.


#include "UtilityFunctions.h"

#include "MS_Define.h"
#include "Manager_Both/MS_TableManager.h"


UClass* UUtilityFunctions::GetClassByTablePathId(int32 aPathId)
{
	const FString Path = gTableMng.GetPath(EMS_TableDataType::BasePathBPFile, aPathId, true);
	
	UClass* Class = StaticLoadClass(UObject::StaticClass(), nullptr, *Path);
	if(!IsValid(Class))
	{
		MS_LOG_VERBOSITY(Error, TEXT("[%s] Class is invalid [PathId : %d] [Path : %s]"), *MS_FUNC_STRING, aPathId, *Path);
		MS_ENSURE(false);

		return nullptr;
	}

	return Class;
}
