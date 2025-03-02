// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_MeshTransformComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTMS_API UMS_MeshTransformComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	UMS_MeshTransformComponent();

protected:
	virtual void BeginPlay() override;

public:
	int32 GetOrder() const { return Order; }

	bool HaveMash() const { return bHaveMash; }
	void SetHaveMash(bool bHave) { bHaveMash = bHave; }

	
protected:
	UPROPERTY(EditAnywhere)
	int32 Order;

	UPROPERTY(EditAnywhere)
	bool bHaveMash;
};
