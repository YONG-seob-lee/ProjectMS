#pragma once

#include "CoreMinimal.h"
#include "AI/AIController/BehaviorTree/Decorator/MS_BehaviorTreeDecorator.h"
#include "Actor/Character/AICharacter/CustomerAICharacter/MS_CustomerAICharacter.h"
#include "MS_CustomerOperatePatternBranchDecorator.generated.h"

UCLASS() class PROJECTMS_API UMS_CustomerOperatePatternBranchDecorator : public UMS_BehaviorTreeDecorator
{
	GENERATED_BODY()

public:
	UMS_CustomerOperatePatternBranchDecorator();

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& aPropertyChangedEvent) override;
	virtual FString GetStaticDescription() const override;
#endif
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory) const override;

	// Property
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) EMS_CustomerOperatePattern ConditionCustomerOperatePattern = EMS_CustomerOperatePattern::Undefined;
};
