#pragma once

#include "CoreMinimal.h"
#include "AI/AIController/BehaviorTree/Task/MS_BehaviorTreeTask.h"
#include "Actor/Character/AICharacter/StaffAICharacter/MS_StaffAICharacter.h"
#include "MS_UpdateStaffBehaviorPattern.generated.h"

UCLASS() class PROJECTMS_API UMS_UpdateStaffBehaviorPattern : public UMS_BehaviorTreeTask
{
	GENERATED_BODY()
	
public:
	UMS_UpdateStaffBehaviorPattern();

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& aPropertyChangedEvent) override;
#endif
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) EMS_StaffObservePattern ConditionStaffObservePattern = EMS_StaffObservePattern::Undefined;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) EMS_StaffOperatePattern ConditionStaffOperatePattern = EMS_StaffOperatePattern::Undefined;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) EMS_StaffInteractPattern ConditionStaffInteractPattern = EMS_StaffInteractPattern::Undefined;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) EMS_StaffIdlePattern ConditionStaffIdlePattern = EMS_StaffIdlePattern::Undefined;
};
