#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MS_StaffAIAnimInstance.generated.h"

UCLASS() class PROJECTMS_API UMS_StaffAIAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UMS_StaffAIAnimInstance();
	
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable) void SetOwnerWorkFlag(const bool& aWorkFlag);
	// Property
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float OwnerMovementSpeed = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool OwnerWorkFlag = false;

	// Instance
public:
	TObjectPtr<class AMS_StaffAICharacter> OwnerInst = nullptr;
};
