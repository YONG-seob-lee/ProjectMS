#pragma once

#include "CoreMinimal.h"
#include "AI/AIController/BehaviorTree/Task/MS_BehaviorTreeTask.h"
#include "Actor/Character/AICharacter/MS_AICharacter.h"
#include "MS_UpdateBehaviorPattern.generated.h"

UCLASS() class PROJECTMS_API UMS_UpdateBehaviorPattern : public UMS_BehaviorTreeTask
{
	GENERATED_BODY()

public:
	UMS_UpdateBehaviorPattern();

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& aPropertyChangedEvent) override;
#endif
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) EMS_AIBehaviorPattern ConditionAIBehaviorPattern = EMS_AIBehaviorPattern::Undefined;
};
