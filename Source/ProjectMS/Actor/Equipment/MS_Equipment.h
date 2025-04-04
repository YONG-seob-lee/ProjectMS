﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_ActorBase.h"
#include "MS_Equipment.generated.h"

UCLASS()
class PROJECTMS_API AMS_Equipment : public AMS_ActorBase
{
	GENERATED_BODY()

public:
	AMS_Equipment(const FObjectInitializer& aObjectInitializer);

protected:
	virtual void BeginPlay() override;

public:
	void ShowEquipment(bool bShow);

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> MeshComponent = nullptr;
};
