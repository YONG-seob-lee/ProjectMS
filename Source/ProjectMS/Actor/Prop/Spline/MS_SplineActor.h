﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_ActorBase.h"
#include "MS_SplineActor.generated.h"

UCLASS()
class PROJECTMS_API AMS_SplineActor : public AMS_ActorBase
{
	GENERATED_BODY()

public:
	AMS_SplineActor(const FObjectInitializer& ObjectInitializer);

	virtual void Tick(float DeltaTime) override;
	
	// aWorldLocation 에서 가장 가까운 스플라인의 접선 벡터를 반환해준다.
	FVector FindTangentClosestToWorldLocation(const FVector& aWorldLocation) const;

	// aWorldLocation 에서 가장 가까운 스플라인의 곡선의 한 점을 반환해준다.
	FVector FindLocationClosestToWorldLocation(const FVector& aWorldLocation) const;

	FORCEINLINE FVector GetStartPoint() const { return StartPoint; }
	FORCEINLINE FVector GetEndPoint() const { return EndPoint; }
	
protected:
	virtual void BeginPlay() override;

	FVector StartPoint = FVector::ZeroVector;
	FVector EndPoint = FVector::ZeroVector;
	
private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class USplineComponent> SplineComponent = nullptr;
};
