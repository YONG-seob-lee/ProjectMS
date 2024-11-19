// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MS_StateBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_StateBase : public UObject
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(uint8 aIndex, const FName& aName);
	virtual void Finalize();

	virtual void Tick(float aDeltaTime) {}
	UFUNCTION()
	void OnBeginState();
	UFUNCTION()
	void OnTickState();
	UFUNCTION()
	void OnExitState();

	FORCEINLINE uint8 GetStateIndex() const { return StateIndex; }
	FORCEINLINE FName GetStateName() const { return StateName; }

protected:
	virtual void Begin() {}
	virtual void Exit() {}

private:	
	UPROPERTY()
	int32 StateIndex = -1;
	UPROPERTY()
	FName StateName = {};
};
