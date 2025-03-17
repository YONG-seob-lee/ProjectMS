// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_ActorBase.h"
#include "MS_MarketFrontActor.generated.h"

UCLASS()
class PROJECTMS_API AMS_MarketFrontActor : public AMS_ActorBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMS_MarketFrontActor(const FObjectInitializer& aObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// Component
	UPROPERTY(BlueprintReadOnly, Meta = (AllowPrivateAccess))
	TObjectPtr<class USphereComponent> SphereComponent = nullptr;
};
