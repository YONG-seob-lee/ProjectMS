// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_BlackboardComponent.h"
#include "MS_OutsideBlackboardComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTMS_API UMS_OutsideBlackboardComponent : public UMS_BlackboardComponent
{
	GENERATED_BODY()

public:
	UMS_OutsideBlackboardComponent();

protected:
	virtual void BeginPlay() override;
};
