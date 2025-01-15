#pragma once

#include "CoreMinimal.h"
#include "AI/AIController/BehaviorTree/Task/MS_BehaviorTreeTask.h"
#include "MS_SearchRandomPatrolLocationTask.generated.h"

UCLASS() class PROJECTMS_API UMS_SearchRandomPatrolLocationTask : public UMS_BehaviorTreeTask
{
	GENERATED_BODY()
	
public:
	UMS_SearchRandomPatrolLocationTask();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory) override;

	// Property
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float PatrolRadius = 150.0f;
};
