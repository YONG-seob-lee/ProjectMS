#pragma once

#include "CoreMinimal.h"
#include "AI/AIController/BehaviorTree/BehaviorTreeDecorator/MS_BehaviorTreeDecorator.h"
#include "Actor/Character/AICharacter/MS_AICharacter.h"
#include "MS_StatePatternBranchDecorator.generated.h"

UCLASS() class PROJECTMS_API UMS_StatePatternBranchDecorator : public UMS_BehaviorTreeDecorator
{
	GENERATED_BODY()
	
public:
	UMS_StatePatternBranchDecorator();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory) const override;
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory) override;
	virtual void OnCeaseRelevant(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory) override;
	virtual void OnNodeActivation(FBehaviorTreeSearchData& aSearchData) override;
	virtual void OnNodeDeactivation(FBehaviorTreeSearchData& aSearchData, EBTNodeResult::Type aNodeResult) override;
	virtual void OnNodeProcessed(FBehaviorTreeSearchData& aSearchData, EBTNodeResult::Type& aNodeResult) override;

#if WITH_EDITOR
	virtual FString GetStaticDescription() const override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& aPropertyChangedEvent) override;
#endif

	// Property
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FBlackboardKeySelector EnumKey = {};
};
