#pragma once

#include "CoreMinimal.h"
#include "AI/AIController/BehaviorTree/BehaviorTreeDecorator/MS_BehaviorTreeDecorator.h"
#include "MS_PrintStringDecorator.generated.h"

UCLASS() class PROJECTMS_API UMS_PrintStringDecorator : public UMS_BehaviorTreeDecorator
{
	GENERATED_BODY()

public:
	UMS_PrintStringDecorator();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnNodeActivation(FBehaviorTreeSearchData& SearchData) override;
	virtual void OnNodeDeactivation(FBehaviorTreeSearchData& SearchData, EBTNodeResult::Type NodeResult) override;
	virtual void OnNodeProcessed(FBehaviorTreeSearchData& SearchData, EBTNodeResult::Type& NodeResult) override;
};
