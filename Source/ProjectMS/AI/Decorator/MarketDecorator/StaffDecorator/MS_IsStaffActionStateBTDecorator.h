

#pragma once

#include "CoreMinimal.h"
#include "AI/Decorator/MS_BTDecorator.h"
#include "MS_IsStaffActionStateBTDecorator.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_IsStaffActionStateBTDecorator : public UMS_BTDecorator
{
	GENERATED_BODY()

public:
	UMS_IsStaffActionStateBTDecorator(const FObjectInitializer& ObjectInitializer);
	
protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;


protected:
	UPROPERTY(EditAnywhere)
	TArray<EMS_StaffActionState> ActionStates;
};
