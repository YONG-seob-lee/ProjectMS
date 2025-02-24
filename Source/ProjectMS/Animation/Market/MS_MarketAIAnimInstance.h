

#pragma once

#include "CoreMinimal.h"
#include "Animation/MS_AIAnimInstance.h"
#include "ContentsUtilities/MS_AIDefine.h"
#include "MS_MarketAIAnimInstance.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE_OneParam(FOnChangeInActionDelegate, bool);

UCLASS()
class PROJECTMS_API UMS_MarketAIAnimInstance : public UMS_AIAnimInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Meta = (BlueprintThreadSafe))
	void SetInAction(bool aInAction);
	
	FORCEINLINE bool IsInAction() const { return bInAction; }

	
private:
	UPROPERTY()
	bool bInAction = false;

public:
	FOnChangeInActionDelegate OnChangeInActionDelegate;
};
