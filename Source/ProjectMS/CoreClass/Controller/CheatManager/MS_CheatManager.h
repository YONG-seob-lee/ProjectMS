// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "MS_CheatManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_CheatManager : public UCheatManager
{
	GENERATED_BODY()
public:
	UFUNCTION(exec,BlueprintCallable,Category="MS Cheat Manager")
	void TestCheatManager(const FString aTestString);
	
	UFUNCTION(exec,BlueprintCallable,Category="MS Cheat Manager")
	void AIChatting(int32 UnitId, const FString& Chatting);
};
