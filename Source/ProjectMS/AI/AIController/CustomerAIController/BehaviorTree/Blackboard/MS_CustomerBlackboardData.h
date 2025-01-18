#pragma once

#include "CoreMinimal.h"
#include "AI/AIController/BehaviorTree/Blackboard/MS_BlackboardData.h"
#include "MS_CustomerBlackboardData.generated.h"

UCLASS() class PROJECTMS_API UMS_CustomerBlackboardData : public UMS_BlackboardData
{
	GENERATED_BODY()
	
public:
	UMS_CustomerBlackboardData();
};
