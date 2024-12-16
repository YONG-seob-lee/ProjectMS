// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MS_ManagementBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_ManagementBase : public UObject
{
	GENERATED_BODY()
public:
	virtual void Initialize();
	virtual void Finalize();
	virtual void PostInitialize();
	virtual void Tick(float aDeltaTime);
};