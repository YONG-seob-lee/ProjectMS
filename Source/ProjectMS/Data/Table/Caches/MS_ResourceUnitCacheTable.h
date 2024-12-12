

#pragma once

#include "CoreMinimal.h"
#include "Table/MS_CacheTable.h"
#include "Table/RowBase/MS_ResourceUnit.h"
#include "MS_ResourceUnitCacheTable.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_ResourceUnitCacheTable : public UMS_CacheTable
{
	GENERATED_BODY()
public:
	virtual void Initialize(TObjectPtr<UMS_TableManager> aMng) override;
	virtual void Finalize() override;

	FMS_ResourceUnit* GetResourceUnitData(int32 aUnitKey);
	
private:
	TMap<int32, FMS_ResourceUnit*> ResourceUnitDatas;
};
