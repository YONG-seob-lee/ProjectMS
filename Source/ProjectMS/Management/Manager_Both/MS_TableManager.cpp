// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_TableManager.h"

#include "ProjectMS/Data/Table/MS_CacheTable.h"
#include "ProjectMS/Data/Table/RowBase/MS_BasePathBPFile.h"
#include "ProjectMS/Data/Table/RowBase/MS_BasePathDirectory.h"
#include "ProjectMS/Utility/MS_Define.h"
#include "Table/Caches/MS_CommonCacheTable.h"
#include "Table/Caches/MS_ItemCacheTable.h"
#include "Table/Caches/MS_LevelCacheTable.h"
#include "Table/Caches/MS_MenuElementCacheTable.h"
#include "Table/Caches/MS_ResourceWidgetCacheTable.h"
#include "Table/Caches/MS_StaffAbilityCacheTable.h"
#include "Table/Caches/MS_StaffCacheTable.h"
#include "Table/Caches/MS_StorageCacheTable.h"
#include "Table/Caches/MS_TutorialCacheTable.h"
#include "Table/RowBase/MS_BasePathImgFile.h"

void FMS_CacheTableData::Finalize()
{
	TablePath = nullptr;
	TableData = nullptr;
	
	if(IsValid(CacheTable))
	{
		CacheTable->Finalize();
		MS_DeleteObject(CacheTable);
	}
}

UMS_TableManager::UMS_TableManager()
{
	TableManager = this;
}

UMS_TableManager::~UMS_TableManager()
{
}

void UMS_TableManager::BuiltInInitialize()
{
	Super::BuiltInInitialize();
}

void UMS_TableManager::PostInitialize()
{
	Super::PostInitialize();
}

void UMS_TableManager::PreFinalize()
{
	Super::PreFinalize();
}

void UMS_TableManager::BuiltInFinalize()
{
	Super::BuiltInFinalize();
}

void UMS_TableManager::Initialize()
{
	if(bInitialize)
	{
		return;
	}
	MakeTableStructData();

	bInitialize = true;
}

void UMS_TableManager::Finalize()
{
	for (auto& CacheTable : CacheTables)
	{
		CacheTable.Value.Finalize();
	}

	CacheTables.Empty();
}

void UMS_TableManager::Tick(float aDeltaTime)
{
	
}

void UMS_TableManager::GetRowDataMap(EMS_TableDataType aTableType, TMap<FName, uint8*>& OutCacher)
{
	const FString& Name = ConvertEnumToString<EMS_TableDataType>("EMS_TableDataType", aTableType);

	const FMS_CacheTableData* CacheTableData = CacheTables.Find(aTableType);
	if (CacheTableData == nullptr)
	{
		return;
	}

	const TObjectPtr<UDataTable> TableData = CacheTableData->GetTableData();
	if (TableData == nullptr)
	{
		return;
	}

	OutCacher = TableData->GetRowMap();
}

FMS_CacheTableData* UMS_TableManager::GetCacheTableData(EMS_TableDataType aTableType)
{
	FMS_CacheTableData* CacheTableData = CacheTables.Find(aTableType);
	if (CacheTableData == nullptr)
	{
		const FString& TableName = ConvertEnumToString<EMS_TableDataType>("EMS_TableDataType", aTableType);
		MS_LOG(TEXT("Wrong Table Type. Please Check (%s) Table Type"), *TableName);
		return nullptr;
	}

	return CacheTableData;
}

FString UMS_TableManager::GetPath(EMS_TableDataType aTableType, int32 aKey, bool bResourcePath)
{
	switch(aTableType)
	{
	case EMS_TableDataType::BasePathBPFile:
		{
			const FMS_BasePathBPFile* RowData = GetTableRowData<FMS_BasePathBPFile>(aTableType, aKey);

			if(RowData == nullptr)
			{
				return FString();
			}
			
			// 테이블로 관리하는 경우 : 경로 + 파일 이름
			return bResourcePath ? GetDirectory(RowData->Directory_Table_Id) + RowData->BP_File_Name.ToString() + '.' + RowData->BP_File_Name.ToString() + TEXT("_C")
			// 관리 안하는 경우 : 레퍼런스 경로
				: FString::Format(TEXT("{0}{1}.{1}"), {GetDirectory(RowData->Directory_Table_Id), RowData->BP_File_Name.ToString()});
		}
		break;
	case EMS_TableDataType::BasePathImgFile:
		{
			const FMS_BasePathImgFile* RowData = GetTableRowData<FMS_BasePathImgFile>(aTableType, aKey);
			
			// 테이블로 관리하는 경우 : 경로 + 파일 이름
			return bResourcePath ? GetDirectory(RowData->Directory_Table_Id) + RowData->Img_File_Name + '.' + RowData->Img_File_Name + TEXT("_C")
			// 관리 안하는 경우 : 레퍼런스 경로
				: FString::Format(TEXT("{0}{1}.{1}"), {GetDirectory(RowData->Directory_Table_Id), RowData->Img_File_Name});
		}
		break;
	default:
		return FString();
	}

	return FString();
}

FString UMS_TableManager::GetDirectory(int32 aDirectoryTableId)
{
	if(aDirectoryTableId == 0 || aDirectoryTableId == INDEX_NONE)
	{
		return FString();
	}

	const FMS_BasePathDirectory* RowData = GetTableRowData<FMS_BasePathDirectory>(EMS_TableDataType::BasePathDirectory, aDirectoryTableId);
	if(RowData == nullptr)
	{
		return FString();
	}
	
	FString ResultDirectory = RowData->Directory.StartsWith(TEXT("/Game/")) ? RowData->Directory : TEXT("/Game/") + RowData->Directory;
	
	return ResultDirectory[ResultDirectory.Len() - 1] != '/' ? ResultDirectory + "/" : ResultDirectory;
}

TObjectPtr<UDataTable> UMS_TableManager::GetTableData(EMS_TableDataType aTableType)
{
	const FMS_CacheTableData* CacheTableData = GetCacheTableData(aTableType);
	if (CacheTableData == nullptr)
	{
		return nullptr;
	}

	return CacheTableData->GetTableData();
}

TObjectPtr<UMS_CacheTable> UMS_TableManager::GetCacheTable(EMS_TableDataType aTableType)
{
	const FMS_CacheTableData* CacheTableData = GetCacheTableData(aTableType);
	if (CacheTableData == nullptr)
	{
		return nullptr;
	}

	return CacheTableData->GetCacheTable();
}

TObjectPtr<UObject> UMS_TableManager::LoadObjectFromFile(const FString& ResourcePath,
	const FMS_LoadResourceDelegate& Delegate, const FString& SubName, int32 Index, bool SubBool)
{
	const FSoftObjectPath Reference = FSoftObjectPath(ResourcePath);
	
	UObject* ResultObject = AssetLoader.LoadSynchronous(Reference);
	if (ResultObject == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Objectnullptr"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ObjectName: %s"), *ResultObject->GetName());
	}

	if(Delegate.IsBound())
	{
		Delegate.Execute(ResourcePath, ResultObject);
	}
	return ResultObject;
}

void UMS_TableManager::ResetData()
{
	CacheTables.Empty();
}

void UMS_TableManager::CreateTableData(EMS_TableDataType aTableType, const FString& aPath, TSubclassOf<UMS_CacheTable> CacherType)
{
	const FString& TableName = ConvertEnumToString<EMS_TableDataType>("EMS_TableDataType", aTableType);

	if (CacheTables.Find(aTableType))
	{
		return;
	}

	// 테이블 데이터 오브젝트 생성
	const TObjectPtr<UDataTable> TableObject = LoadTableObjectFromFile(aPath, TableName, FMS_LoadResourceDelegate::CreateUObject(this, &UMS_TableManager::LoadComplete));
	if (TableObject == nullptr)
	{
		return;
	}

	// 매퍼 생성 및 초기화
	if(CacherType)
	{
		const TObjectPtr<UMS_CacheTable> CacheTable = MS_NewObject<UMS_CacheTable>(this, CacherType);
		if (CacheTable == nullptr)
		{
			return;
		}
		// 추가.
		CacheTables.Emplace(aTableType, FMS_CacheTableData(aPath, TableObject, CacheTable));
		
		CacheTable->Initialize(this);
	}
	else
	{
		CacheTables.Emplace(aTableType, FMS_CacheTableData(aPath, TableObject, nullptr));
	}
}

void UMS_TableManager::MakeTableStructData()
{
	ResetData();

	// [Add TableData] CreateTableData(EnumType, RowDataPath);
	CreateTableData(EMS_TableDataType::Common, TEXT("/Game/TableData/Common"), UMS_CommonCacheTable::StaticClass());
	CreateTableData(EMS_TableDataType::BasePathDirectory, TEXT("/Game/TableData/BasePath_Directory"));
	CreateTableData(EMS_TableDataType::BasePathBPFile, TEXT("/Game/TableData/BasePath_BP_File"));
	CreateTableData(EMS_TableDataType::BasePathImgFile, TEXT("/Game/TableData/BasePath_Img_File"));
	
	CreateTableData(EMS_TableDataType::Level, TEXT("/Game/TableData/Level.Level"), UMS_LevelCacheTable::StaticClass());
	CreateTableData(EMS_TableDataType::ResourceWidget, TEXT("/Game/TableData/ResourceWidget.ResourceWidget"), UMS_ResourceWidgetCacheTable::StaticClass());

	CreateTableData(EMS_TableDataType::ItemData, TEXT("/Game/TableData/ItemData.ItemData"), UMS_ItemCacheTable::StaticClass());
	CreateTableData(EMS_TableDataType::Storage, TEXT("/Game/TableData/Storage.Storage"), UMS_StorageCacheTable::StaticClass());
	CreateTableData(EMS_TableDataType::Staff, TEXT("/Game/TableData/Staff.Staff"), UMS_StaffCacheTable::StaticClass());
	CreateTableData(EMS_TableDataType::StaffAbility, TEXT("/Game/TableData/StaffAbility.StaffAbility"), UMS_StaffAbilityCacheTable::StaticClass());
	CreateTableData(EMS_TableDataType::MenuElement, TEXT("/Game/TableData/MenuElement.MenuElement"), UMS_MenuElementCacheTable::StaticClass());
	CreateTableData(EMS_TableDataType::Tutorial, TEXT("/Game/TableData/Tutorial.Tutorial"), UMS_TutorialCacheTable::StaticClass());
}

void UMS_TableManager::LoadComplete(const FString& aTableName, TObjectPtr<UObject> aTableData)
{
}

UMS_TableManager* UMS_TableManager::GetInstance()
{
	return TableManager;
}
