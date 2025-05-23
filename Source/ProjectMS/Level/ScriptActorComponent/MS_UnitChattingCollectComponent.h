﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "MS_MarketLevelScriptActorComponent.h"

struct FMS_ChattingParameter
{
	FMS_ChattingParameter() {}

	FMS_ChattingParameter(int32 aUnitHandleId, int32 aMinute, const FText& aChatting)
	: UnitHandle(aUnitHandleId), bIsInMarket(true), Minute(aMinute), Chatting(aChatting) {}
	
	FMS_ChattingParameter(int32 aUnitHandleId, bool abIsInMarket, int32 aMinute, const FText& aChatting)
	: UnitHandle(aUnitHandleId), bIsInMarket(abIsInMarket), Minute(aMinute), Chatting(aChatting) {}
	
	int32 UnitHandle = INDEX_NONE;
	bool bIsInMarket = false;
	
	int32 Minute = 0;
	FText Chatting = FText(); 
};
#include "CoreMinimal.h"
#include "MS_Define.h"
#include "MS_UnitChattingCollectComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_UnitChattingCollectComponent : public UMS_MarketLevelScriptActorComponent
{
	GENERATED_BODY()
public:
	virtual void Initialize() override;
	virtual void Finalize() override;
	
	void SetOnUpdateChatting(FMS_ChattingParameter aParameter);

	void GetUnitsHandle(TMap<MS_Handle, bool>& aUnitsHandle);
	void GetUnitChatting(MS_Handle aUnitHandle, TArray<FMS_ChattingParameter>& aParameters);
	void GetAllChatting(TArray<FMS_ChattingParameter>& aChattingCollection) const;

#if WITH_EDITOR
	void TestInitialize(int32 aUnitHandle);
	bool IsUnitInMarket(int32 aUnitHandle);
#endif
private:
	// Key : UnitHandle, Value : Value's Key is TimeStamp, Value's Value is LocalizedStringTableId
	TMap<MS_Handle, TArray<FMS_ChattingParameter>> ChattingCollection;
	TArray<FMS_ChattingParameter> TimelineChattingCollection;
};