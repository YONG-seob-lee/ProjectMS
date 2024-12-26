#pragma once

#include "CoreMinimal.h"
#include "AI/AIController/BehaviorTree/Decorator/MS_BehaviorTreeDecorator.h"
#include "Actor/Character/AICharacter/StaffAICharacter/MS_StaffAICharacter.h"
#include "MS_StaffObservePatternBranchDecorator.generated.h"

UCLASS() class PROJECTMS_API UMS_StaffObservePatternBranchDecorator : public UMS_BehaviorTreeDecorator
{
	GENERATED_BODY()
	
public:
	UMS_StaffObservePatternBranchDecorator();

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& aPropertyChangedEvent) override;
	virtual FString GetStaticDescription() const override;
#endif
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& aOwnerComp, uint8* aNodeMemory) const override;

	// Property
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) EMS_StaffObservePattern ConditionStaffObservePattern = EMS_StaffObservePattern::Undefined;
};
