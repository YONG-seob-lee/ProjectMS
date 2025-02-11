// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MS_AIAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_AIAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeBeginPlay() override;
	
	FORCEINLINE void SetIsActWalking(bool _bActWalking) { bActWalking = _bActWalking; }
	FORCEINLINE bool IsActWalking() const { return bActWalking; }
private:

	UPROPERTY(Category = AIAnimInstance, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bActWalking = true;
};
