// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "MS_NightProp.generated.h"

UCLASS()
class PROJECTMS_API AMS_NightProp : public AActor
{
	GENERATED_BODY()

public:
	AMS_NightProp();

	FORCEINLINE bool IsContainMesh() const { return StaticMeshComponent != nullptr; }
	
	void TurnOnLight() const;
	void TurnOffLight() const;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	TWeakObjectPtr<UStaticMeshComponent> StaticMeshComponent = nullptr;
	TWeakObjectPtr<class USpotLightComponent> SpotLightComponent = nullptr;
};
