// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_Actor.h"
#include "MS_Equipment.generated.h"

UCLASS()
class PROJECTMS_API AMS_Equipment : public AMS_Actor
{
	GENERATED_BODY()

public:
	AMS_Equipment(const FObjectInitializer& aObjectInitializer);

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UMeshComponent> MeshComponent = nullptr;
};
