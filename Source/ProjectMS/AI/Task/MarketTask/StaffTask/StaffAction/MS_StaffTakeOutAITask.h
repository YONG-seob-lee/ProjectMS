

#pragma once

#include "CoreMinimal.h"
#include "AI/Task/MS_AITask.h"
#include "MS_StaffTakeOutAITask.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_StaffTakeOutAITask : public UMS_AITask
{
	GENERATED_BODY()
	
	UMS_StaffTakeOutAITask(const FObjectInitializer& ObjectInitializer);
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
