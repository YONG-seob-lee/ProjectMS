// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Environment/MS_LevelPropDatas.h"
#include "MS_GridBoxComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTMS_API UMS_GridBoxComponent : public UBoxComponent
{
	GENERATED_BODY()

public:
	UMS_GridBoxComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;


	// Property :: Getter
	FVector GetGridLocationOffset() const { return GridLocationOffset; }
	
	EMS_PropSpaceType GetPropSpaceType() const { return PropSpaceType; }

	
private:
	// Property
	UPROPERTY(EditDefaultsOnly)
	FVector GridLocationOffset;
	
	UPROPERTY(EditDefaultsOnly)
	EMS_PropSpaceType PropSpaceType;
};
