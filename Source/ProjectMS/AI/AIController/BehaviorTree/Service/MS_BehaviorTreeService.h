#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "MS_BehaviorTreeService.generated.h"

UCLASS() class PROJECTMS_API UMS_BehaviorTreeService : public UBTService
{
	GENERATED_BODY()
	
public:
	UMS_BehaviorTreeService();

	virtual void OnSearchStart(FBehaviorTreeSearchData& SearchData) override;
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
