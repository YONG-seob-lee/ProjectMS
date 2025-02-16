// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Mode/ModeObject/Supervisor/MS_AISupervisor.h"
#include "MS_StaffSupervisor.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_StaffSupervisor : public UMS_AISupervisor
{
	GENERATED_BODY()

public:
	UMS_StaffSupervisor();
	
	virtual void Initialize() override;
	virtual void Finalize() override;

	virtual void Tick(float aDeltaTime) override;
	
	virtual void Begin() override;
	virtual void Exit() override;
};
