// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_BlackboardComponent.h"
#include "MS_CustomerBlackboardComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTMS_API UMS_CustomerBlackboardComponent : public UMS_BlackboardComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMS_CustomerBlackboardComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
								FActorComponentTickFunction* ThisTickFunction) override;
};
