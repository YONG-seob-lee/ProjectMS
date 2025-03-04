// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Decorator/MS_BTDecorator.h"
#include "ContentsUtilities/MS_AIDefine.h"
#include "MS_IsCustomerActionStateBTDecorator.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_IsCustomerActionStateBTDecorator : public UMS_BTDecorator
{
	GENERATED_BODY()

public:
	UMS_IsCustomerActionStateBTDecorator(const FObjectInitializer& ObjectInitializer);
	
protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;


protected:
	UPROPERTY(EditAnywhere)
	TArray<EMS_CustomerActionState> ActionStates;
};
