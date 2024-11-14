// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Management/MS_ManagerBase.h"
#include "MS_InputManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_InputManager : public UMS_ManagerBase
{
	GENERATED_BODY()
public:
	virtual void BuiltInInitialize() override;
	virtual void Initialize() override;
	virtual void PostInitialize() override;
	virtual void PreFinalize() override;
	virtual void Finalize() override;
	virtual void BuiltInFinalize() override;

	virtual void Tick(float aDeltaTime) override;
};
