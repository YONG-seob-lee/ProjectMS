// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MS_AISupervisor.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_AISupervisor : public UObject
{
	GENERATED_BODY()

public:
	UMS_AISupervisor();
	
	virtual void Initialize();
	virtual void Finalize();

	virtual void Tick(float aDeltaTime);
	
	virtual void Begin();
	virtual void Exit();
};
