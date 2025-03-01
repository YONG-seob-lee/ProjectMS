// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/Market/MS_MarketAIAnimInstance.h"
#include "MS_CustomerAIAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_CustomerAIAnimInstance : public UMS_MarketAIAnimInstance
{
	GENERATED_BODY()
public:
	FORCEINLINE void SetActionState(EMS_CustomerActionState aActionProcess) { ActionProcess = aActionProcess; }
	FORCEINLINE EMS_CustomerActionState GetActionProcess() const { return ActionProcess; }
	
protected:
	UPROPERTY(Category = AIAnimInstance, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EMS_CustomerActionState ActionProcess = EMS_CustomerActionState::None;
};
