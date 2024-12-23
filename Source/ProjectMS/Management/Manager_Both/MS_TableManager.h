// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StreamableManager.h"
#include "Management/MS_ManagerBase.h"
#include "MS_TableManager.generated.h"

DECLARE_DELEGATE_TwoParams(FMS_LoadResourceDelegate, const FString&, TObjectPtr<UObject>);

UENUM()
enum class EMS_TableDataType : uint8
{
	Common = 0						UMETA(DisplayName = "Common"),
	ResourceWidget					UMETA(DisplayName = "ResourceWidget"),
	ResourceUnit					UMETA(DisplayName = "ResourceUnit"),

	BasePathDirectory				UMETA(DisplayName = "BasePathDirectory"),
	BasePathBPFile					UMETA(DisplayName = "BasePathBP_File"),
	BasePathImgFile					UMETA(DisplayName = "BasePathImgFile"),

	Level							UMETA(DisplayName = "Level"),
	PlayerStatus					UMETA(DisplayName = "PlayerStatus"),
	Enemy							UMETA(DisplayName = "Enemy"),
	
	Env_Zone						UMETA(DisplayName = "Env_Zone"),
	Env_Prop_FloorTile				UMETA(DisplayName = "Env_Prop_FloorTile"),

	Item							UMETA(DisplayName = "Item"),
	SaleStand						UMETA(DisplayName = "SaleStand"),
	MenuElement						UMETA(DisplayName = "MenuElement"),
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
class PROJECTMS_API  UMS_TableManager : public UMS_ManagerBase
{
	GENERATED_BODY()

public:
	UMS_TableManager();
	virtual ~UMS_TableManager() override;

public:
	virtual void BuiltInInitialize() override;
	virtual void Initialize() override;
	virtual void PostInitialize() override;
	virtual void PreFinalize() override;
	virtual void Finalize() override;
	virtual void BuiltInFinalize() override;

	virtual void Tick(float aDeltaTime) override;

	virtual void GetRowDataMap(EMS_TableDataType aTableType, TMap<FName, uint8*>& aOutCache);

	FMS_CacheTableData* GetCacheTableData(EMS_TableDataType aTableType);
	FString GetPath(EMS_TableDataType aTableType, int32 aKey, bool bResourcePath = false);
	FString GetDirectory(int32 aDirectoryTableId);
	
	TObjectPtr<UDataTable> GetTableData(EMS_TableDataType aTableType);

	
	TObjectPtr<UMS_CacheTable> GetCacheTable(EMS_TableDataType aTableType);
	
	template<typename FRowData>
	FRowData* GetTableRowData(EMS_TableDataType aTableType, int32 aKey)
	{
		const FMS_CacheTableData* CacheTable = GetCacheTableData(aTableType);
		if (CacheTable == nullptr)  
		{
			return nullptr;
		}

		const TObjectPtr<UDataTable> TableData = CacheTable->GetTableData();
		const FName KeyName = FName(FString::FromInt(aKey));
		const FString Context = TEXT("GENERAL");
		return TableData->FindRow<FRowData>(KeyName, Context);
	}

	int32 GetTableRowNum(EMS_TableDataType aTableType)
	{
		const FMS_CacheTableData* CacheTable = GetCacheTableData(aTableType);
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
	void CreateTableData(EMS_TableDataType aTableType, const FString& aPath, TSubclassOf<UMS_CacheTable> aCacheType = nullptr);
	void MakeTableStructData();

	void LoadComplete(const FString& aTableName, TObjectPtr<UObject> aTableData);
	
	UPROPERTY()
	TMap<EMS_TableDataType, FMS_CacheTableData> CacheTables;

	bool bInitialize = false;

public:
	inline static TObjectPtr<UMS_TableManager> TableManager = nullptr;
	static UMS_TableManager* GetInstance();
	
#define gTableMng (*UMS_TableManager::GetInstance())
};
