// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_TableManager.h"

#include "ProjectMS/Data/Table/MS_CacheTable.h"
#include "ProjectMS/Data/Table/RowBase/MS_BasePathBPFile.h"
#include "ProjectMS/Data/Table/RowBase/MS_BasePathDirectory.h"
#include "ProjectMS/Utility/MS_Define.h"

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
}

UMS_TableManager::~UMS_TableManager()
{
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

void UMS_TableManager::GetRowDataMap(EMS_TableDataType TableType, TMap<FName, uint8*>& OutCacher)
{
	const FString& Name = ConvertEnumToString<EMS_TableDataType>("EMS_TableDataType", TableType);

	const FMS_CacheTableData* CacheTableData = CacheTables.Find(TableType);
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

FMS_CacheTableData* UMS_TableManager::GetCacheTableData(EMS_TableDataType TableType)
{
	FMS_CacheTableData* CacheTableData = CacheTables.Find(TableType);
	if (CacheTableData == nullptr)
	{
		const FString& TableName = ConvertEnumToString<EMS_TableDataType>("EMS_TableDataType", TableType);
		MS_LOG(TEXT("Wrong Table Type. Please Check (%s) Table Type"), *TableName);
		return nullptr;
	}

	return CacheTableData;
}

FString UMS_TableManager::GetPath(EMS_TableDataType TableType, int32 Key, bool bResourcePath)
{
	switch(TableType)
	{
	case EMS_TableDataType::BasePath_BP_File:
		{
			const FMS_BasePathBPFile* RowData = GetTableRowData<FMS_BasePathBPFile>(TableType, Key);

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
	case EMS_TableDataType::BasePath_Img_File:
		{
			// const FBasePath_Img_File* RowData = GetTableRowData<FBasePath_Img_File>(TableType, Key);
			//
			// // 테이블로 관리하는 경우 : 경로 + 파일 이름
			// return bResourcePath ? GetDirectory(RowData->Directory_Table_Id) + RowData->Img_File_Name + '.' + RowData->Img_File_Name + TEXT("_C")
			// // 관리 안하는 경우 : 레퍼런스 경로
			// 	: FString::Format(TEXT("{0}{1}.{1}"), {GetDirectory(RowData->Directory_Table_Id), RowData->Img_File_Name});
		}
		break;
	default:
		return FString();
	}

	return FString();
}

FString UMS_TableManager::GetDirectory(int32 DirectoryTableId)
{
	if(DirectoryTableId == 0 || DirectoryTableId == INDEX_NONE)
	{
		return FString();
	}

	const FMS_BasePathDirectory* RowData = GetTableRowData<FMS_BasePathDirectory>(EMS_TableDataType::BasePath_Directory, DirectoryTableId);
	if(RowData == nullptr)
	{
		return FString();
	}
	
	FString ResultDirectory = RowData->Directory.StartsWith(TEXT("/Game/")) ? RowData->Directory : TEXT("/Game/") + RowData->Directory;
	
	return ResultDirectory[ResultDirectory.Len() - 1] != '/' ? ResultDirectory + "/" : ResultDirectory;
}

TObjectPtr<UDataTable> UMS_TableManager::GetTableData(EMS_TableDataType TableType)
{
	const FMS_CacheTableData* CacheTableData = GetCacheTableData(TableType);
	if (CacheTableData == nullptr)
	{
		return nullptr;
	}

	return CacheTableData->GetTableData();
}

TObjectPtr<UMS_CacheTable> UMS_TableManager::GetCacheTable(EMS_TableDataType TableType)
{
	const FMS_CacheTableData* CacheTableData = GetCacheTableData(TableType);
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

void UMS_TableManager::CreateTableData(EMS_TableDataType TableType, const FString& Path, TSubclassOf<UMS_CacheTable> CacherType)
{
	const FString& TableName = ConvertEnumToString<EMS_TableDataType>("EMS_TableDataType", TableType);

	if (CacheTables.Find(TableType))
	{
		return;
	}

	// 테이블 데이터 오브젝트 생성
	const TObjectPtr<UDataTable> TableObject = LoadTableObjectFromFile(Path, TableName, FMS_LoadResourceDelegate::CreateUObject(this, &UMS_TableManager::LoadComplete));
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
		CacheTables.Emplace(TableType, FMS_CacheTableData(Path, TableObject, CacheTable));
		
		CacheTable->Initialize(this);
	}
	else
	{
		CacheTables.Emplace(TableType, FMS_CacheTableData(Path, TableObject, nullptr));
	}
}

void UMS_TableManager::MakeTableStructData()
{
	ResetData();

	// [Add TableData] CreateTableData(EnumType, RowDataPath);
}

void UMS_TableManager::LoadComplete(const FString& TableName, TObjectPtr<UObject> TableData)
{
}
