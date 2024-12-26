#pragma once

#include "CoreMinimal.h"
#include "AI/AIController/BehaviorTree/Decorator/MS_BehaviorTreeDecorator.h"
#include "MS_PrintStringDecorator.generated.h"

UCLASS() class PROJECTMS_API UMS_PrintStringDecorator : public UMS_BehaviorTreeDecorator
{
	GENERATED_BODY()

public:
	UMS_PrintStringDecorator();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory) const override;
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory) override;
	virtual void OnCeaseRelevant(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory) override;
	virtual void OnNodeActivation(FBehaviorTreeSearchData& aSearchData) override;
	virtual void OnNodeDeactivation(FBehaviorTreeSearchData& aSearchData, EBTNodeResult::Type aNodeResult) override;
	virtual void OnNodeProcessed(FBehaviorTreeSearchData& aSearchData, EBTNodeResult::Type& aNodeResult) override;
};
