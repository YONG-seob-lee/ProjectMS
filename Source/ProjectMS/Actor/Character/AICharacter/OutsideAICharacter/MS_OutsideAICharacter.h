// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AICharacter/MS_AICharacter.h"
#include "MS_OutsideAICharacter.generated.h"

UCLASS()
class PROJECTMS_API AMS_OutsideAICharacter : public AMS_AICharacter
{
	GENERATED_BODY()
	
public:
	
	AMS_OutsideAICharacter();

	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float aDeltaTime) override;

	MS_Handle GetUnitHandle() const;
private:
	TObjectPtr<class AMS_DuckSplineActor> FindNearestSpline() const;

	TWeakObjectPtr<class AMS_DuckSplineActor> NearestSpline = nullptr;
	
	UPROPERTY(EditAnywhere)
	float DuckVelocity = 1.3f;
};
