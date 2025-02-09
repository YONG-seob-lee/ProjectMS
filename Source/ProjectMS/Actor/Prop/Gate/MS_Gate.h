// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Prop/MS_Prop.h"
#include "MS_Gate.generated.h"

UCLASS()
class PROJECTMS_API AMS_Gate : public AMS_Prop
{
	GENERATED_BODY()

public:
	AMS_Gate(const FObjectInitializer& aObjectInitializer);

protected:
	virtual void BeginPlay() override;


private:
	// Gate Data
	UPROPERTY(EditInstanceOnly, Category=MS_Gate)
	int32 GateIndex;

	UPROPERTY(EditInstanceOnly, Category=MS_Gate)
	int32 LinkedGateIndex;
};
