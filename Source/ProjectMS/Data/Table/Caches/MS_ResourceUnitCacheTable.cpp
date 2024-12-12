#include "MS_ResourceUnitCacheTable.h"

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

FMS_ResourceUnit* UMS_ResourceUnitCacheTable::GetResourceUnitData(int32 aUnitKey)
{
	if(FMS_ResourceUnit** UnitData = ResourceUnitDatas.Find(aUnitKey))
	{
		return *UnitData;
	}

	return nullptr;
}
