// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

struct FMS_ChattingParameter
{
	FMS_ChattingParameter() {}
	FMS_ChattingParameter(int32 aUnitHandleId, int32 aMinute, const FText& aChatting) : UnitHandle(aUnitHandleId), bIsInMarket(true), Minute(aMinute), Chatting(aChatting) {}
	FMS_ChattingParameter(int32 aUnitHandleId, bool abIsInMarket, int32 aMinute, const FText& aChatting) : UnitHandle(aUnitHandleId), bIsInMarket(abIsInMarket), Minute(aMinute), Chatting(aChatting) {}
	
	int32 UnitHandle = INDEX_NONE;
	bool bIsInMarket = false;
	
	int32 Minute = 0;
	FText Chatting = FText(); 
};
#include "CoreMinimal.h"
#include "MarketLevelScriptActorComponent.h"
#include "MS_Define.h"
#include "MS_UnitChattingCollectComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_UnitChattingCollectComponent : public UMarketLevelScriptActorComponent
{
	GENERATED_BODY()
public:
	void Initialize();
	void Finalize() const;
	
	void SetOnUpdateChatting(FMS_ChattingParameter aParameter);

	void GetUnitsHandle(TMap<MS_Handle, bool>& aUnitsHandle);
	void GetUnitChatting(MS_Handle aUnitHandle, TArray<FMS_ChattingParameter>& aParameters);
	void GetAllChatting(TMap<MS_Handle, TArray<FMS_ChattingParameter>>& aChattingCollection) const;

private:
	// Key : UnitHandle, Value : Value's Key is TimeStamp, Value's Value is LocalizedStringTableId
	TMap<MS_Handle, TArray<FMS_ChattingParameter>> ChattingCollection;
};