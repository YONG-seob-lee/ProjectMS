// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AICharacter/MS_AICharacter.h"
#include "MS_OutsideAICharacter.generated.h"

UCLASS()
class PROJECTMS_API AMS_OutsideAICharacter : public AMS_AICharacter
{
	GENERATED_BODY()
	
public:
	
	AMS_OutsideAICharacter();

	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float aDeltaTime) override;
	FORCEINLINE TObjectPtr<class UMS_AIAnimInstance> GetAnimInstance() { return AnimInstance; }

private:
	TObjectPtr<class UMS_AIAnimInstance> AnimInstance = nullptr;
};
