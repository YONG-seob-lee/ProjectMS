// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ContentsUtilities/MS_AIDefine.h"
#include "UObject/Object.h"
#include "MS_PersonalAction.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_PersonalAction : public UObject
{
	GENERATED_BODY()

public:
	static bool HasPersonalActionTarget(EMS_PersonalActionType aPersonalActionType);
};
