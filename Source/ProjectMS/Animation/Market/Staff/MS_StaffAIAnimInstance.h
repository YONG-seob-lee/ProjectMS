

#pragma once

#include "CoreMinimal.h"
#include "Animation/Market/MS_MarketAIAnimInstance.h"
#include "MS_StaffAIAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_StaffAIAnimInstance : public UMS_MarketAIAnimInstance
{
	GENERATED_BODY()

public:
	FORCEINLINE void SetActionState(EMS_StaffActionState aActionState) { ActionState = aActionState; }
	FORCEINLINE EMS_StaffActionState GetActionProcess() const { return ActionState; }

	
protected:
	UPROPERTY(Category = AIAnimInstance, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EMS_StaffActionState ActionState = EMS_StaffActionState::None;
};
