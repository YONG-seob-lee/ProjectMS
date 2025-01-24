// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_Define.h"
#include "MS_MarketLevelScriptActorComponent.h"
#include "MS_UnitPurchaseCollectComponent.generated.h"

struct FMS_PurchaseParameter
{
	FMS_PurchaseParameter() {}
	
	FMS_PurchaseParameter(int32 aUnitHandle, int32 aItemId, int32 aItemCount)
	: UnitHandle(aUnitHandle), ItemId(aItemId), ItemCount(aItemCount) {}

	int32 UnitHandle = INDEX_NONE;
	int32 ItemId = 0;
	int32 ItemCount = 0;
};

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_UnitPurchaseCollectComponent : public UMS_MarketLevelScriptActorComponent
{
	GENERATED_BODY()
public:
	virtual void Initialize() override;
	virtual void Finalize() override;

	void SetOnUpdatePurchase(FMS_PurchaseParameter aParameter);

	void GetUnitPurchase(MS_Handle aHandle, TArray<FMS_PurchaseParameter>& aParameters);
	void GetAllUnitPurchase(TMap<int32, int32>& aPurchaseItemList);
	
private:
	TMap<MS_Handle, TArray<FMS_PurchaseParameter>> PurchaseCollection;
};
