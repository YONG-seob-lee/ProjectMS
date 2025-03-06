// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_MarketAIUnit.h"
#include "Component/Actor/MS_AIParameterComponent.h"
#include "ContentsUtilities/MS_AIDefine.h"
#include "Table/Caches/MS_CustomerCacheTable.h"
#include "MS_CustomerAIUnit.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_CustomerAIUnit : public UMS_MarketAIUnit
{
	GENERATED_BODY()

public:
	virtual void Initialize(MS_Handle aUnitHandle, EMS_UnitType aUnitType, int32 aTableId) override;
	virtual void Finalize() override;
	virtual void PostInitialize() override;
	virtual void Tick(float aDeltaTime) override;

protected:
	virtual int32 GetBlueprintPathId() const override;
	virtual UClass* GetBlueprintClass() const override;

public:
	// Action
	EMS_CustomerActionType GetFirstCustomerAction();

	void RegisterCustomerAction(EMS_CustomerActionType aCustomerActionType);
	void UnregisterCustomerAction(EMS_CustomerActionType aCustomerActionType);
	
	bool IsVisitBefore(int32 StorageUnitHandle) const;
	void AddVisitStorageUnitHandle(MS_Handle StorageHandle);
	MS_Handle GetTargetStorageUnitHandle();
	
	bool IsAnyItemInDisplay();
	void GetRemainItems(TMap<int32, int32>& RemainItems);
	void PickUpItem(int32 PickUpItemTableId, int32 PickUpItemCount);
	void ShowPickItem(bool bShow) const;
	void Paid();
	bool IsPickUpAllItems();
	bool IsExceptAnyWannaItem();
	
	// Spline
	bool FindNearestSpline();
	bool ReachSplineEndPoint() const;
	FVector GetSplineEndPointPosition() const;
	bool ReachSplineStartPoint() const;
	void GoingToMarket() const;
	void GoingToHome() const;
	
	FORCEINLINE FString& GetCustomerName() { return CustomerData.GetName(); }
	
	// Behavior
	void EventBehavior(EMS_BehaviorType aBehaviorType) const;

	// Purchase
	void EventPurchase() const;

private:
	FMS_CustomerData CustomerData = FMS_CustomerData();
	
	TWeakObjectPtr<class AMS_CustomerSplineActor> CustomerSplineActor = nullptr;

	TArray<EMS_CustomerActionType> CustomerActions = {};

	TArray<MS_Handle> VisitStorageUnitHandles = {};
};
