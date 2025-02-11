// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_Actor.h"
#include "MS_DuckSplineActor.generated.h"

UCLASS()
class PROJECTMS_API AMS_DuckSplineActor : public AMS_Actor
{
	GENERATED_BODY()

public:
	AMS_DuckSplineActor(const FObjectInitializer& ObjectInitializer);

	virtual void Tick(float DeltaTime) override;

	// aWorldLocation 에서 가장 가까운 스플라인의 접선 벡터를 반환해준다.
	FVector FindTangentClosestToWorldLocation(const FVector& aWorldLocation) const;

	// aWorldLocation 에서 가장 가까운 스플라인의 곡선의 한 점을 반환해준다.
	FVector FindLocationClosestToWorldLocation(const FVector& aWorldLocation) const;
protected:
	virtual void BeginPlay() override;

private:
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<class USplineComponent> SplineComponent = nullptr;
};
