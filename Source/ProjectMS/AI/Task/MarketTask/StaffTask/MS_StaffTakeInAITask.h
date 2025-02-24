

#pragma once

#include "CoreMinimal.h"
#include "AI/Task/MS_AITask.h"
#include "MS_StaffTakeInAITask.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_StaffTakeInAITask : public UMS_AITask
{
	GENERATED_BODY()

public:
	UMS_StaffTakeInAITask(const FObjectInitializer& ObjectInitializer);
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
