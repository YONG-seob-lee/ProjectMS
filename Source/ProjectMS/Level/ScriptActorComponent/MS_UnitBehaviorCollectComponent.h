// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_Define.h"
#include "MS_MarketLevelScriptActorComponent.h"
#include "MS_UnitBehaviorCollectComponent.generated.h"

struct FMS_BehaviorParameter
{
	FMS_BehaviorParameter() {}

	FMS_BehaviorParameter(int32 aUnitHandleId, int32 aMinute, const FText& aBehavior)
	: UnitHandle(aUnitHandleId), Minute(aMinute), Behavior(aBehavior) {}
	
	
	int32 UnitHandle = INDEX_NONE;
	int32 Minute = 0;
	FText Behavior = FText(); 
};
/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_UnitBehaviorCollectComponent : public UMS_MarketLevelScriptActorComponent
{
	GENERATED_BODY()
public:
	virtual void Initialize() override;
	virtual void Finalize() override;
	
	void SetOnUpdateBehavior(FMS_BehaviorParameter aParameter);

	void GetUnitBehavior(MS_Handle aUnitHandle, TArray<FMS_BehaviorParameter>& aParameters);
	void GetAllBehavior(TArray<FMS_BehaviorParameter>& aBehaviorCollection) const;
	
private:
	// Key : UnitHandle, Value : Value's Key is TimeStamp, Value's Value is LocalizedStringTableId
	TMap<MS_Handle, TArray<FMS_BehaviorParameter>> BehaviorCollection;
	TArray<FMS_BehaviorParameter> TimelineBehaviorCollection;
};
