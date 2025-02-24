

#pragma once

#include "CoreMinimal.h"
#include "AI/Decorator/MS_BTDecorator.h"
#include "MS_IsStaffActionProcessBTDecorator.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_IsStaffActionProcessBTDecorator : public UMS_BTDecorator
{
	GENERATED_BODY()

public:
	UMS_IsStaffActionProcessBTDecorator(const FObjectInitializer& ObjectInitializer);
	
protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;


protected:
	UPROPERTY(EditAnywhere)
	TArray<EMS_StaffActionState> ActionProcesses;
};
