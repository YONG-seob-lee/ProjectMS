#pragma once

#include "CoreMinimal.h"
#include "AI/AIController/BehaviorTree/BehaviorTreeTask/MS_BehaviorTreeTask.h"
#include "MS_ExecuteSubBehaviorTreeTask.generated.h"

UCLASS() class PROJECTMS_API UMS_ExecuteSubBehaviorTreeTask : public UMS_BehaviorTreeTask
{
	GENERATED_BODY()
	
public:
	UMS_ExecuteSubBehaviorTreeTask();

	// Property
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FBlackboardKeySelector SubBehaviorTreeKey = {};
};
