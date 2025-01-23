// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "MS_ChatElementData.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_ChatElementData : public UObject
{
	GENERATED_BODY()
public:
	FORCEINLINE void SetUnitHandle(int32 aUnitHandle) { UnitHandle = aUnitHandle; }
	FORCEINLINE void SetMinute(int32 aMinute) { Minute = aMinute; }
	FORCEINLINE void SetChatting(const FText& aChatting) { Chatting = aChatting; }

	FORCEINLINE int32 GetUnitHandle() const { return UnitHandle; }
	FORCEINLINE int32 GetMinute() const { return Minute; }
	FORCEINLINE FText GetChatting() { return Chatting; }

private:
	int32 UnitHandle = INDEX_NONE;
	int32 Minute = 0;
	FText Chatting = FText();
};
