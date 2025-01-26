// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Prop/MS_Prop.h"
#include "MS_Wall.generated.h"

UCLASS()
class PROJECTMS_API AMS_Wall : public AMS_Prop
{
	GENERATED_BODY()

public:
	AMS_Wall(const FObjectInitializer& aObjectInitializer);

protected:
	virtual void BeginPlay() override;

public:
	void GetGridPositionOnBothSides(FIntVector2& OutGridPosition1, FIntVector2& OutGridPosition2) const;
	
	void SetVisibilityByGridOpened(class AMS_ConstructibleLevelScriptActorBase* OwnerLevelScriptActor);
};
