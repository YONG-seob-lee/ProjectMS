﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Decorator/MS_BTDecorator.h"
#include "MS_IsCustomerPutDownAllItemsBTDecorator.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_IsCustomerPutDownAllItemsBTDecorator : public UMS_BTDecorator
{
	GENERATED_BODY()
	
public:
	UMS_IsCustomerPutDownAllItemsBTDecorator(const FObjectInitializer& ObjectInitializer);
	
protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
