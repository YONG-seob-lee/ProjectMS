// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Mode/ModeObject/Supervisor/MS_AISupervisor.h"
#include "MS_CustomerSupervisor.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_CustomerSupervisor : public UMS_AISupervisor
{
	GENERATED_BODY()

public:
	UMS_CustomerSupervisor();
	
	virtual void Initialize() override;
	virtual void Finalize() override;

	virtual void Tick(float aDeltaTime) override;
	
	virtual void Begin() override;
	virtual void Exit() override;
};
