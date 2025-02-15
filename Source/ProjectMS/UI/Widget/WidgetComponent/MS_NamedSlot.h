// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/NamedSlot.h"
#include "MS_NamedSlot.generated.h"

UENUM()
enum class EMS_TutorialDirection
{
	None = 0,
};

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_NamedSlot : public UNamedSlot
{
	GENERATED_BODY()
public:

private:
	//EMS_TutorialDirection 
};
