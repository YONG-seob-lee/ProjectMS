#pragma once

#include "CoreMinimal.h"
#include "AI/AIController/BehaviorTree/Service/MS_BehaviorTreeService.h"
#include "MS_PrintStringService.generated.h"

UCLASS() class PROJECTMS_API UMS_PrintStringService : public UMS_BehaviorTreeService
{
	GENERATED_BODY()
	
public:
	UMS_PrintStringService();

	virtual void OnSearchStart(FBehaviorTreeSearchData& SearchData) override;
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	// Property
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FString StringToPrint = {};
};
