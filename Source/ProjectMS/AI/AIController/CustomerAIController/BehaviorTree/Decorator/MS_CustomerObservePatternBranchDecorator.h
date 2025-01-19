#pragma once

#include "CoreMinimal.h"
#include "AI/AIController/BehaviorTree/Decorator/MS_BehaviorTreeDecorator.h"
#include "Actor/Character/AICharacter/CustomerAICharacter/MS_CustomerAICharacter.h"
#include "MS_CustomerObservePatternBranchDecorator.generated.h"

UCLASS() class PROJECTMS_API UMS_CustomerObservePatternBranchDecorator : public UMS_BehaviorTreeDecorator
{
	GENERATED_BODY()

public:
	UMS_CustomerObservePatternBranchDecorator();

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& aPropertyChangedEvent) override;
	virtual FString GetStaticDescription() const override;
#endif
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory) const override;

	// Property
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) EMS_CustomerObservePattern ConditionCustomerObservePattern = EMS_CustomerObservePattern::Undefined;
};
