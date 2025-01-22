#include "MS_ResourceUnitCacheTable.h"

#include "Table/MS_UnitBaseCacheTable.h"

void UMS_ResourceUnitCacheTable::Initialize(TObjectPtr<UMS_TableManager> aMng)
{
	Super::Initialize(aMng);

	ResourceUnitDatas.Empty();
	
	BuildTable(aMng, EMS_TableDataType::ResourceUnit, ResourceUnitDatas);
}

void UMS_ResourceUnitCacheTable::Finalize()
{
	Super::Finalize();
}

FMS_ResourceUnit* UMS_ResourceUnitCacheTable::GetResourceUnitData(int32 aUnitTableId) const
{
	if(ResourceUnitDatas.Contains(aUnitTableId))
	{
		FMS_ResourceUnit* UnitData = *ResourceUnitDatas.Find(aUnitTableId);
		return UnitData;
	}

	return nullptr;
}

int32 UMS_ResourceUnitCacheTable::GetBlueprintPathId(int32 aUnitTableId, int32 aChildTableId) const
{
	FMS_ResourceUnit* ResourceUnitData = GetResourceUnitData(aUnitTableId);
	if (ResourceUnitData == nullptr)
	{
		MS_LOG_Verbosity(Error, TEXT("[%s] ResourceUnitData is nullptr [Key : %d]"), *MS_FUNC_STRING, aUnitTableId);
		MS_Ensure(false);

		return INDEX_NONE;
	}

	EMS_TableDataType ChildTableType = static_cast<EMS_TableDataType>(ResourceUnitData->ChildTableDataType);
	
	UMS_UnitBaseCacheTable* UnitBaseCacheTable = Cast<UMS_UnitBaseCacheTable>(gTableMng.GetCacheTable(ChildTableType));
	if (UnitBaseCacheTable == nullptr)
	{
		MS_LOG_Verbosity(Error, TEXT("[%s] UnitBaseCacheTable is nullptr [TableType : %d]"), *MS_FUNC_STRING, ResourceUnitData->ChildTableDataType);
		MS_Ensure(false);

		return INDEX_NONE;
	}

	int32 BPPathId = UnitBaseCacheTable->GetUnitBaseBPIndex(aChildTableId);
	if (BPPathId == INDEX_NONE)
	{
		MS_LOG_Verbosity(Error, TEXT("[%s] BPPathId is invalid [TableType : %d] [TableId : %d]"), *MS_FUNC_STRING, ResourceUnitData->ChildTableDataType, aChildTableId);
		MS_Ensure(false);

		return INDEX_NONE;
	}

	return BPPathId;
}

UClass* UMS_ResourceUnitCacheTable::GetBlueprintClass(int32 aUnitTableId, int32 aChildTableId) const
{
	int32 BPPathId = GetBlueprintPathId(aUnitTableId, aChildTableId);
	if (BPPathId == INDEX_NONE)
	{
		return nullptr;
	}

	const FString BPPath = gTableMng.GetPath(EMS_TableDataType::BasePathBPFile, BPPathId, true);
	
	UClass* BPClass = StaticLoadClass(UObject::StaticClass(), nullptr, *BPPath);
	if(!IsValid(BPClass))
	{
		MS_LOG_Verbosity(Error, TEXT("[%s] BPClass is invalid [BPPathId : %d] [BPPath : %s]"), *MS_FUNC_STRING, BPPathId, *BPPath);
		MS_Ensure(false);

		return nullptr;
	}

	return BPClass;
}

FString UMS_ResourceUnitCacheTable::GetUnitName(MS_Handle aUnitHandle)
{
	if(FMS_ResourceUnit** ResourceUnitData = ResourceUnitDatas.Find(aUnitHandle))
	{
		return (*ResourceUnitData)->UnitName;
	}

	return FString();
}

void UMS_ResourceUnitCacheTable::GetUnitsName(TArray<MS_Handle>& aUnitsTableId, TArray<FString>& aUnitsName)
{
	aUnitsName.Empty();
	
	for(const auto& UnitTableId : aUnitsTableId)
	{
		if(FMS_ResourceUnit** ResourceUnitData = ResourceUnitDatas.Find(UnitTableId))
		{
			aUnitsName.Emplace((*ResourceUnitData)->UnitName);
		}
	}
}
