#pragma once

#include "CoreMinimal.h"
#include "AI/AIController/BehaviorTree/Task/MS_BehaviorTreeTask.h"
#include "MS_PrintTextTask.generated.h"

UCLASS() class PROJECTMS_API UMS_PrintTextTask : public UMS_BehaviorTreeTask
{
	GENERATED_BODY()

public:
	UMS_PrintTextTask();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory) override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory) override;

	// Property
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FString StringToPrint = {};
};
