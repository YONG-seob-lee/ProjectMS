// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StreamableManager.h"
#include "UObject/Object.h"
#include "MS_TableManager.generated.h"

DECLARE_DELEGATE_TwoParams(FMS_LoadResourceDelegate, const FString&, TObjectPtr<UObject>);

UENUM()
enum class EMS_TableDataType : uint8
{
	Common = 0						UMETA(DisplayName = "Common"),
	Resource_Widget					UMETA(DisplayName = "Resource_Widget"),
	Resource_Unit					UMETA(DisplayName = "Resource_Unit"),

	BasePath_Directory				UMETA(DisplayName = "BasePath_Directory"),
	BasePath_BP_File				UMETA(DisplayName = "BasePath_BP_File"),
	BasePath_Img_File				UMETA(DisplayName = "BasePath_Img_File"),

	PlayerStatus					UMETA(DisplayName = "PlayerStatus"),
	Enemy							UMETA(DisplayName = "Enemy"),
};

USTRUCT()
struct FMS_CacheTableData
{
	GENERATED_USTRUCT_BODY()
public:
	FMS_CacheTableData() {}
	
	FMS_CacheTableData(const FString& aTablePath, const TObjectPtr<UDataTable>& aTableData, const TObjectPtr<class UMS_CacheTable>& aCacheTable) 
							: TablePath(aTablePath), TableData(aTableData), CacheTable(aCacheTable) {}
	~FMS_CacheTableData() { TableData = nullptr; CacheTable = nullptr; }

	void Finalize();
	
	FORCEINLINE const FString& GetTablePath() { return TablePath; }
	FORCEINLINE TObjectPtr<UDataTable> GetTableData() const { return TableData; }
	FORCEINLINE TObjectPtr<UMS_CacheTable> GetCacheTable() const { return CacheTable; }
private:
	FString TablePath = FString();
	
	UPROPERTY()
	TObjectPtr<UDataTable> TableData = nullptr;
	UPROPERTY()
	TObjectPtr<UMS_CacheTable> CacheTable = nullptr;
};

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_TableManager : public UObject
{
	GENERATED_BODY()

public:
	UMS_TableManager();
	~UMS_TableManager();

	virtual void Initialize();
	virtual void Finalize();
	virtual void Tick(float aDeltaTime);

	virtual void GetRowDataMap(EMS_TableDataType TableType, TMap<FName, uint8*>& OutCache);

	FMS_CacheTableData* GetCacheTableData(EMS_TableDataType TableType);
	FString GetPath(EMS_TableDataType TableType, int32 Key, bool bResourcePath = false);
	FString GetDirectory(int32 DirectoryTableId);
	
	TObjectPtr<UDataTable> GetTableData(EMS_TableDataType TableType);

	
	TObjectPtr<UMS_CacheTable> GetCacheTable(EMS_TableDataType TableType);
	
	template<typename FRowData>
	FRowData* GetTableRowData(EMS_TableDataType TableType, int32 Key)
	{
		const FMS_CacheTableData* CacheTable = GetCacheTableData(TableType);
		if (CacheTable == nullptr)  
		{
			return nullptr;
		}

		const TObjectPtr<UDataTable> TableData = CacheTable->GetTableData();
		const FName KeyName = FName(FString::FromInt(Key));
		const FString Context = TEXT("GENERAL");
		return TableData->FindRow<FRowData>(KeyName, Context);
	}

	int32 GetTableRowNum(EMS_TableDataType TableType)
	{
		const FMS_CacheTableData* CacheTable = GetCacheTableData(TableType);
		if (CacheTable == nullptr)
		{
			return 0;
		}

		if(const TObjectPtr<UDataTable> TableData = CacheTable->GetTableData())
		{
			return TableData->GetRowMap().Num();
		}
		return 0;
	}

	// 임시
	FStreamableManager AssetLoader;
	TObjectPtr<UObject> LoadObjectFromFile(const FString& ResourcePath, const FMS_LoadResourceDelegate& Delegate = nullptr, const FString& SubName = TEXT("SubName"), int32 Index = 0, bool SubBool = false);
	//
	
private:
	void ResetData();
	void CreateTableData(EMS_TableDataType TableType, const FString& Path, TSubclassOf<UMS_CacheTable> CacheType = nullptr);
	void MakeTableStructData();

	void LoadComplete(const FString& TableName, TObjectPtr<UObject> TableData);
	
	UPROPERTY()
	TMap<EMS_TableDataType, FMS_CacheTableData> CacheTables;

	bool bInitialize = false;
	
#define	gTableMng (*UMS_TableManager::GetInstance())
};
