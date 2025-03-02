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

	UFUNCTION(Exec,BlueprintCallable,Category="MS Cheat Manager")
	void AIComeInMarket(int32 UnitId);

	UFUNCTION(Exec,BlueprintCallable,Category="MS Cheat Manager")
	void AIExitMarket(int32 UnitId);

	UFUNCTION(exec,BlueprintCallable,Category="MS Cheat Manager")
	void AIChatting(int32 UnitId, const FString& Chatting);

	UFUNCTION(exec,BlueprintCallable,Category="MS Cheat Manager")
	void AIBehavior(int32 UnitId, const FString& Behavior);

	UFUNCTION(exec,BlueprintCallable,Category="MS Cheat Manager")
	void AIPurchase(int32 UnitId, int32 ItemId, int32 ItemCount);

	UFUNCTION(exec,BlueprintCallable,Category="MS Cheat Manager")
	void AddStaff(int32 aStaffId);

	UFUNCTION(exec,BlueprintCallable,Category="MS Cheat Manager")
	void RemoveAllStaff();

	UFUNCTION(exec,BlueprintCallable,Category="MS Cheat Manager")
	void DayNight(bool bTurnNight, bool bDirectly = true);

	UFUNCTION(exec,BlueprintCallable,Category="MS Cheat Manager")
	void RequestDialog(FString DialogType = TEXT("흰오리 : 안녕하세요 \'디디마켓\' 홍보대사 \"흰오리\" 인사드립니다. 오늘 다양한 상품을 판매 하고 있사오니 많이들 찾아와주세요. 갑사합니다~!"), float TypeSpeed = 0.1f);


	UFUNCTION(exec,BlueprintCallable,Category="MS Cheat Manager")
	void ResetProcessTutorial();

	UFUNCTION(exec,BlueprintCallable,Category="MS Cheat Manager")
	void FastRun(int32 aMultiply);
#endif
};
