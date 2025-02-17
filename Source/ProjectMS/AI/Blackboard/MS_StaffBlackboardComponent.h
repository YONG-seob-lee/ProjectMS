// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Blackboard/MS_BlackboardComponent.h"
#include "MS_StaffBlackboardComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTMS_API UMS_StaffBlackboardComponent : public UMS_BlackboardComponent
{
	GENERATED_BODY()

public:
	UMS_StaffBlackboardComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
