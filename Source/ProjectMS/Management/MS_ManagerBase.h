// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MS_ManagerBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_ManagerBase : public UObject
{
	GENERATED_BODY()
	
public:
	virtual ~UMS_ManagerBase() {}
	
	virtual void BuiltInInitialize() {}
	virtual void Initialize() {}
	virtual void PostInitialize() {}
	virtual void PreFinalize() {}
	virtual void Finalize() {}
	virtual void BuiltInFinalize() {}

	virtual void Tick(float aDeltaTime) {}

	virtual void BeginPlay() {}
};
