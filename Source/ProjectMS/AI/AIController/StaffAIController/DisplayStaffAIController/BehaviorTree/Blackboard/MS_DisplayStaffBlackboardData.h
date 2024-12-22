#pragma once

#include "CoreMinimal.h"
#include "AI/AIController/StaffAIController/BehaviorTree/Blackboard/MS_StaffBlackboardData.h"
#include "MS_DisplayStaffBlackboardData.generated.h"

UCLASS() class PROJECTMS_API UMS_DisplayStaffBlackboardData : public UMS_StaffBlackboardData
{
	GENERATED_BODY()

public:
	UMS_DisplayStaffBlackboardData();
};
