

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

	UFUNCTION()
	void SetIsStopped(bool aIsStopped);
	
	FORCEINLINE bool IsInAction() const { return bInAction; }

	FORCEINLINE void SetEquipmentName(const FName& aEquipmentName) { EquipmentName = aEquipmentName; }

	
private:
	UPROPERTY()
	bool bInAction = false;

protected:
	UPROPERTY(BlueprintReadOnly)
	bool bIsStopped = false;
	
	UPROPERTY(BlueprintReadOnly)
	FName EquipmentName;

public:
	FOnChangeInActionDelegate OnChangeInActionDelegate;
};
