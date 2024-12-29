#pragma once

#include "CoreMinimal.h"
#include "Utility/MS_Define.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MS_BehaviorTreeTask.generated.h"

UCLASS() class PROJECTMS_API UMS_BehaviorTreeTask : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UMS_BehaviorTreeTask();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory) override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory, float aDeltaSeconds) override;
	virtual void OnMessage(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory, FName aMessage, int32 aRequestID, bool abSuccess) override;
	virtual void OnTaskFinished(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory, EBTNodeResult::Type aTaskResult) override;
};
