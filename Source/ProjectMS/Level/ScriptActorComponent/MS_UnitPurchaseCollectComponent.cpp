// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_UnitPurchaseCollectComponent.h"

#include "Manager_Both/MS_UnitManager.h"

void UMS_UnitPurchaseCollectComponent::Initialize()
{
	gUnitMng.OnPurchaseDelegate.AddUObject(this, &UMS_UnitPurchaseCollectComponent::SetOnUpdatePurchase);
}

void UMS_UnitPurchaseCollectComponent::Finalize()
{
	gUnitMng.OnPurchaseDelegate.RemoveAll(this);
}

void UMS_UnitPurchaseCollectComponent::SetOnUpdatePurchase(FMS_PurchaseParameter aParameter)
{
	if(TArray<FMS_PurchaseParameter>* Parameters = PurchaseCollection.Find(aParameter.UnitHandle))
	{
		Parameters->Emplace(aParameter);
	}
	else
	{
		TArray<FMS_PurchaseParameter> UnitPurchaseParameterArray;
		UnitPurchaseParameterArray.Emplace(aParameter);
		PurchaseCollection.Emplace(aParameter.UnitHandle, UnitPurchaseParameterArray);
	}
}

void UMS_UnitPurchaseCollectComponent::GetUnitPurchase(MS_Handle aUnitHandle, TArray<FMS_PurchaseParameter>& aParameters)
{
	aParameters.Empty();
	
	if(const TArray<FMS_PurchaseParameter>* Parameters = PurchaseCollection.Find(aUnitHandle))
	{
		aParameters = *Parameters;
	}
}

void UMS_UnitPurchaseCollectComponent::GetAllUnitPurchase(TMap<int32, int32>& aPurchaseItemList)
{
	aPurchaseItemList.Empty();

	for(const auto& UnitPurchaseData : PurchaseCollection)
	{
		for(const auto& PurchaseParameter : UnitPurchaseData.Value)
		{
			if(const int32* PurchaseItemCount = aPurchaseItemList.Find(PurchaseParameter.ItemId))
			{
				aPurchaseItemList.Emplace(PurchaseParameter.ItemId, *PurchaseItemCount + PurchaseParameter.ItemCount);
			}
			else
			{
				aPurchaseItemList.Emplace(PurchaseParameter.ItemId, PurchaseParameter.ItemCount);
			}
		}
	}
}

#if WITH_EDITOR
void UMS_UnitPurchaseCollectComponent::TestInitialize(int32 aUnitHandle)
{
	PurchaseCollection.Emplace(aUnitHandle, {});
}
#endif
