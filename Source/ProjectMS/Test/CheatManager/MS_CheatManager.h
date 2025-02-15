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
#if WITH_EDITOR
	UFUNCTION(exec,BlueprintCallable,Category="MS Cheat Manager")
	void TestCheatManager(const FString aTestString);
#endif
	
#if WITH_EDITOR
	UFUNCTION(Exec,BlueprintCallable,Category="MS Cheat Manager")
	void AIComeInMarket(int32 UnitId);
#endif
	
#if WITH_EDITOR
	UFUNCTION(Exec,BlueprintCallable,Category="MS Cheat Manager")
	void AIExitMarket(int32 UnitId);
#endif
	
#if WITH_EDITOR
	UFUNCTION(exec,BlueprintCallable,Category="MS Cheat Manager")
	void AIChatting(int32 UnitId, const FString& Chatting);
#endif
	
#if WITH_EDITOR
	UFUNCTION(exec,BlueprintCallable,Category="MS Cheat Manager")
	void AIBehavior(int32 UnitId, const FString& Behavior);
#endif
	
#if WITH_EDITOR
	UFUNCTION(exec,BlueprintCallable,Category="MS Cheat Manager")
	void AIPurchase(int32 UnitId, int32 ItemId, int32 ItemCount);
#endif

		
#if WITH_EDITOR
	UFUNCTION(exec,BlueprintCallable,Category="MS Cheat Manager")
	void DayNight(bool bTurnNight, bool bDirectly = true);
#endif

#if WITH_EDITOR
	UFUNCTION(exec,BlueprintCallable,Category="MS Cheat Manager")
	void RequestDialog(FString DialogType = TEXT("흰오리 : 안녕하세요 \'디디마켓\' 홍보대사 \"흰오리\" 인사드립니다. 오늘 다양한 상품을 판매 하고 있사오니 많이들 찾아와주세요. 갑사합니다~!"), float TypeSpeed = 0.1f);
#endif

#if WITH_EDITOR
	UFUNCTION(exec,BlueprintCallable,Category="MS Cheat Manager")
	void RequestTutorial(int32 t);
#endif
		
#if WITH_EDITOR
	UFUNCTION(exec,BlueprintCallable,Category="MS Cheat Manager")
	void ResetProcessTutorial();
#endif
};
