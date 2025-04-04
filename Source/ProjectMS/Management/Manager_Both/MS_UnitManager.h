﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Management/MS_ManagerBase.h"
#include "ScriptActorComponent/MS_UnitBehaviorCollectComponent.h"
#include "ScriptActorComponent/MS_UnitChattingCollectComponent.h"
#include "ScriptActorComponent/MS_UnitPurchaseCollectComponent.h"
#include "Utility/MS_Define.h"
#include "MS_UnitManager.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnUpdateChattingDelegate, FMS_ChattingParameter);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnUpdateBehaviorDelegate, FMS_BehaviorParameter);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnUpdatePurchaseDelegate, FMS_PurchaseParameter);
/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_UnitManager : public UMS_ManagerBase
{
	GENERATED_BODY()

public:
	UMS_UnitManager();
	virtual void Finalize() override;

	TWeakObjectPtr<class UMS_UnitBase> GetUnit(MS_Handle aHandle);
	void GetUnits(EMS_UnitType aUnitType, TArray<TWeakObjectPtr<UMS_UnitBase>>& aOutUnits);

	TWeakObjectPtr<class UMS_UnitBase> CreateUnit(EMS_UnitType aUnitType, int32 aTableId, bool bCreateActor = true, const FVector& aPosition = FVector::ZeroVector, const FRotator& aRotator = FRotator::ZeroRotator);
	void DestroyUnit(MS_Handle aHandle);
	void DestroyUnit(TWeakObjectPtr<UMS_UnitBase> aUnit);
	void DestroyUnits(TArray<TWeakObjectPtr<UMS_UnitBase>>& aUnits);
	void DestroyAllUnits(EMS_UnitType aUnitType);
	void DestroyAllUnits();

	FOnUpdateChattingDelegate OnChattingDelegate;
	FOnUpdateBehaviorDelegate OnBehaviorDelegate;
	FOnUpdatePurchaseDelegate OnPurchaseDelegate;
	
protected:
	void DestroyUnit_Internal(TWeakObjectPtr<class UMS_UnitBase> aUnitBase);

private:
	TSubclassOf<UMS_UnitBase> GetUnitTypeClass(EMS_UnitType aUnitType);
	
	MS_Handle MakeUnitHandle();
	
private:
	UPROPERTY()
	TMap<uint32, TObjectPtr<UMS_UnitBase>> Units;
	
	TMultiMap<EMS_UnitType, TWeakObjectPtr<UMS_UnitBase>> CacheUnitTypeToUnits;

	uint32 LastUnitHandle = InvalidUnitHandle;

public:
	inline static TObjectPtr<UMS_UnitManager> UnitManager = nullptr;
	static UMS_UnitManager* GetInstance();

	TMap<EMS_UnitType, TSubclassOf<UMS_UnitBase>> UnitTypeClasses;
#define gUnitMng (*UMS_UnitManager::GetInstance())
};
