// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_Define.h"
#include "Level/MS_ConstructibleLevelScriptActorBase.h"
#include "ScriptActorComponent/MS_UnitBehaviorCollectComponent.h"
#include "ScriptActorComponent/MS_UnitChattingCollectComponent.h"
#include "ScriptActorComponent/MS_UnitPurchaseCollectComponent.h"
#include "MS_MarketLevelScriptActor.generated.h"

UCLASS()
class PROJECTMS_API AMS_MarketLevelScriptActor : public AMS_ConstructibleLevelScriptActorBase
{
	GENERATED_BODY()

public:
	AMS_MarketLevelScriptActor();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void PostInitializeComponents() override;

public:
	virtual void Tick(float DeltaTime) override;
	
	void GetUnitsHandle(TArray<MS_Handle>& aUnitsHandle) const;
	int32 GetComeInMarketPeoplePerDay() const;
	void GetUnitComeMarketData(MS_Handle aUnitHandle, int32& ComeInMinute, int32& ComeOutMinute) const;
	
	// AI Chatting
	void GetUnitChatting(MS_Handle aUnitHandle, TArray<FMS_ChattingParameter>& aParameters) const;
	void GetAllChattingCollection(TArray<FMS_ChattingParameter>& aChattingCollection) const;

	// AI Behavior
	void GetUnitBehavior(MS_Handle aUnitHandle, TArray<FMS_BehaviorParameter>& aParameters) const;
	void GetAllBehaviorCollection(TArray<FMS_BehaviorParameter>& aBehaviorCollection) const;
	
	// AI Purchase
	void GetUnitPurchase(MS_Handle aUnitHandle, TArray<FMS_PurchaseParameter>& aParameters) const;
	void GetAllPurchaseCollection(TMap<int32, int32>& aPurchaseCollection) const;

#if WITH_EDITOR
	void AddTestAIActorComeInMarket(int32 aUnitId) const;
	bool IsUnitInMarket(int32 aUnitHandle) const;
#endif
	
private:
	void InitializePlayerDataFurnitures();
	
	void UpdateMinute(int32 _Minute);
	void UpdateDirectionalLight(float _BrightValue) const;
private:
	UPROPERTY()
	TObjectPtr<class UMS_UnitChattingCollectComponent> ChattingCollectComponent = nullptr;

	UPROPERTY()
	TObjectPtr<class UMS_UnitBehaviorCollectComponent> BehaviorCollectComponent = nullptr;
	
	UPROPERTY()
	TObjectPtr<class UMS_UnitPurchaseCollectComponent> PurchaseCollectComponent = nullptr;
};
