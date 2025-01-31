// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Level/MS_LevelDefine.h"
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
	class AMS_Prop* GetOwnerProp() const;
	
	EMS_PropSpaceType GetPropSpaceType() const { return PropSpaceType; }
	
	EMS_PurposeType GetPropPurposeSpaceType() const { return PropPurposeSpaceType; }


	// Grid Position
	// 이동과 회전값이 적용된 상태에서 좌상단 기준으로 계산
	void GetGridPositions(FIntVector2& aOutStartGridPosition, FIntVector2& aOutGridNum) const;

	
private:
	// Property
	UPROPERTY(EditDefaultsOnly)
	EMS_PropSpaceType PropSpaceType;

	UPROPERTY(EditDefaultsOnly)
	EMS_PurposeType PropPurposeSpaceType;
};
