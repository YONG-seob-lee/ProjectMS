

#pragma once

#include "CoreMinimal.h"
#include "AI/Task/MS_AITask.h"
#include "ContentsUtilities/MS_AIDefine.h"
#include "MS_ChangeStaffActionProcessAITask.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_ChangeStaffActionProcessAITask : public UMS_AITask
{
	GENERATED_BODY()

public:
	UMS_ChangeStaffActionProcessAITask(const FObjectInitializer& ObjectInitializer);
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere)
	EMS_StaffActionProcess ActionProcess;
};
