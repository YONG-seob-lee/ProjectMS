#pragma once

#include "CoreMinimal.h"
#include "AI/AIController/BehaviorTree/Task/MS_BehaviorTreeTask.h"
#include "Actor/Character/AICharacter/CustomerAICharacter/MS_CustomerAICharacter.h"
#include "MS_UpdateCustomerBehaviorPattern.generated.h"

UCLASS() class PROJECTMS_API UMS_UpdateCustomerBehaviorPattern : public UMS_BehaviorTreeTask
{
	GENERATED_BODY()

public:
	UMS_UpdateCustomerBehaviorPattern();

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& aPropertyChangedEvent) override;
#endif
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) EMS_CustomerObservePattern ConditionCustomerObservePattern = EMS_CustomerObservePattern::Undefined;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) EMS_CustomerOperatePattern ConditionCustomerOperatePattern = EMS_CustomerOperatePattern::Undefined;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) EMS_CustomerInteractPattern ConditionCustomerInteractPattern = EMS_CustomerInteractPattern::Undefined;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) EMS_CustomerIdlePattern ConditionCustomerIdlePattern = EMS_CustomerIdlePattern::Undefined;
};
