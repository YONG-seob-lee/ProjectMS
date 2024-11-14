// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Utility/MS_Define.h"
#include "MS_CacheTable.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_CacheTable : public UObject
{
	GENERATED_BODY()
public:
	virtual void Initialize(TObjectPtr<class UMS_TableManager> aMng) {}
	virtual void Finalize() {}

	template<typename T>
	static void BuildTable(TObjectPtr<UMS_TableManager> aTableManager, EMS_TableDataType aType, TMap<int32, T*>& aCacheTable)
	{
		TMap<FName, uint8*> RowData;
		aTableManager->GetRowDataMap(aType, RowData);

		aCacheTable.Reset();
		for (auto& Pair : RowData)
		{
			// 열 데이터의 id 값 산출
			int32 Id = FCString::Atoi(*Pair.Key.ToString());
			// 해당 구조체를 명시하여 캐스팅(구조체가 다르면 안되니까 무조건 강제 고정 캐스팅)
			T* Data = reinterpret_cast<T*>(Pair.Value);
			if (Id > 0 && Data)
			{
				aCacheTable.Emplace(Id, Data);
			}
			else
			{
				MS_LOG(TEXT("Table Id or Data is Wrong!!!!!!. PleaseCheck ExcelTable or TableType"));
			}
		}
	}
};
