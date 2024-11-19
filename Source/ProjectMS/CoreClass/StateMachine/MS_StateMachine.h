// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MS_StateMachine.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_StateMachine : public UObject
{
	GENERATED_BODY()
public:
	void Create();
	void Destroy();
	void Tick(float aDeltaTime);

	void RegisterState(int8 aIndex, const FName& aName, const TSubclassOf<class UMS_StateBase>& aSceneType, UObject* aOuter = nullptr);
	void UnRegisterStates();

	TObjectPtr<UMS_StateBase> GetCurrentState();

	void GetActiveStateId(TArray<int8>& aActiveState) const;

	void SetState(int32 aIndex, bool bInstant = true);

	TObjectPtr<UMS_StateBase> GetState(int32 aIndex) const;
private:
	void SetState_Internal(uint8 aIndex);
	
	UPROPERTY()
	TMap<int8, TObjectPtr<UMS_StateBase>> EntireState;

	uint8 PreviousStateId = -1;
	uint8 CurrentStateId = -1;
	uint8 ChangeStateId = -1;
};
