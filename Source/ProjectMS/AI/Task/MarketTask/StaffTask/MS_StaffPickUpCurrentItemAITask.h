

#pragma once

#include "CoreMinimal.h"
#include "AI/Task/MS_AITask.h"
#include "MS_StaffPickUpCurrentItemAITask.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_StaffPickUpCurrentItemAITask : public UMS_AITask
{
	GENERATED_BODY()

public:
	UMS_StaffPickUpCurrentItemAITask(const FObjectInitializer& ObjectInitializer);
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
