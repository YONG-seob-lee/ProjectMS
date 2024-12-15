#pragma once

#include "CoreMinimal.h"
#include "AI/AIController/BehaviorTree/Blackboard/MS_BlackboardData.h"
#include "MS_StaffBlackboardData.generated.h"

UCLASS(BlueprintType, Blueprintable, EditInlineNew) class PROJECTMS_API UMS_StaffBlackboardData : public UMS_BlackboardData
{
	GENERATED_BODY()
	
public:
	UMS_StaffBlackboardData();
};
