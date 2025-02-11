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
	bool AnimIsFinished() { return false; }

private:
};
