// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MS_Pawn.generated.h"

UCLASS()
class PROJECTMS_API AMS_Pawn : public APawn
{
	GENERATED_BODY()

public:
	AMS_Pawn();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float aDeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* aPlayerInputComponent) override;
};
