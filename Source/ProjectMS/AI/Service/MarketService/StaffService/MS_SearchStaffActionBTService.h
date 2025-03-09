// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Service/MS_BTService.h"
#include "MS_SearchStaffActionBTService.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_SearchStaffActionBTService : public UMS_BTService
{
	GENERATED_BODY()

public:
	UMS_SearchStaffActionBTService(const FObjectInitializer& ObjectInitializer);
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
