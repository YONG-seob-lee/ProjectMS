

#pragma once

#include "CoreMinimal.h"
#include "Table/MS_CacheTable.h"
#include "Table/RowBase/MS_MenuElement.h"
#include "MS_MenuElementCacheTable.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_MenuElementCacheTable : public UMS_CacheTable
{
	GENERATED_BODY()
public:
	virtual void Initialize(TObjectPtr<UMS_TableManager> aMng) override;
	virtual void Finalize() override;

	void GetMenuData(TArray<TObjectPtr<class UMS_MenuElementData>>& aMenuElements);
private:
	TMap<int32, FMS_MenuElement*> MenuElements;
};