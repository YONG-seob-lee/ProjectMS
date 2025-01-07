#pragma once

#include "CoreMinimal.h"
#include "AI/AIController/BehaviorTree/Task/MS_BehaviorTreeTask.h"
#include "MS_ResetStaffBlackboardData.generated.h"

UCLASS() class PROJECTMS_API UMS_ResetStaffBlackboardData : public UMS_BehaviorTreeTask
{
	GENERATED_BODY()
	
public:
	UMS_ResetStaffBlackboardData();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory) override;
};
