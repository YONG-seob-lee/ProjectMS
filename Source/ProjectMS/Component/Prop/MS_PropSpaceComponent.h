// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Environment/MS_LevelPropDatas.h"
#include "MS_PropSpaceComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTMS_API UMS_PropSpaceComponent : public UBoxComponent
{
	GENERATED_BODY()

public:
	UMS_PropSpaceComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	
	
	// Property :: Getter
	EMS_PropSpaceType GetPropSpaceType() const { return PropSpaceType; }
	EMS_PurposeType GetPropPurposeSpaceType() const { return PropPurposeSpaceType; }
	
	void GetGridPositions(FIntVector& aOutWorldStartGridPosition, FIntVector& aOutGridNum) const;

	class AMS_Prop* GetOwnerProp() const;

	
private:
	// Property
	UPROPERTY(EditDefaultsOnly)
	EMS_PropSpaceType PropSpaceType;

	UPROPERTY(EditDefaultsOnly)
	EMS_PurposeType PropPurposeSpaceType;
};
