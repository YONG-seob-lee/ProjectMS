#pragma once

#include "CoreMinimal.h"
#include "AI/AIController/BehaviorTree/Decorator/MS_BehaviorTreeDecorator.h"
#include "Actor/Character/AICharacter/MS_AICharacter.h"
#include "MS_BehaviorPatternBranchDecorator.generated.h"

UCLASS() class PROJECTMS_API UMS_BehaviorPatternBranchDecorator : public UMS_BehaviorTreeDecorator
{
	GENERATED_BODY()
	
public:
	UMS_BehaviorPatternBranchDecorator();

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& aPropertyChangedEvent) override;
	virtual FString GetStaticDescription() const override;
#endif
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory) const override;

	// Property
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) EMS_AIBehaviorPattern ConditionAIBehaviorPattern = EMS_AIBehaviorPattern::Undefined;
};
