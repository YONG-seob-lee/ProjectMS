

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
	FORCEINLINE void SetActionProcess(EMS_StaffActionState aActionProcess) { ActionProcess = aActionProcess; }
	FORCEINLINE EMS_StaffActionState GetActionProcess() const { return ActionProcess; }

	
protected:
	UPROPERTY(Category = AIAnimInstance, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EMS_StaffActionState ActionProcess = EMS_StaffActionState::None;
};
