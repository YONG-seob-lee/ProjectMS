#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "Utility/MS_Define.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MS_BehaviorTreeDecorator.generated.h"

UCLASS() class PROJECTMS_API UMS_BehaviorTreeDecorator : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UMS_BehaviorTreeDecorator();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory) const override;
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory) override;
	virtual void OnCeaseRelevant(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory) override;
	virtual void OnNodeActivation(FBehaviorTreeSearchData& aSearchData) override;
	virtual void OnNodeDeactivation(FBehaviorTreeSearchData& aSearchData, EBTNodeResult::Type aNodeResult) override;
	virtual void OnNodeProcessed(FBehaviorTreeSearchData& aSearchData, EBTNodeResult::Type& aNodeResult) override;
};
