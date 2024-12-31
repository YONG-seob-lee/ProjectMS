// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_LevelScriptActorBase.h"
#include "MS_TownLevelScriptActor.generated.h"

UCLASS()
class PROJECTMS_API AMS_TownLevelScriptActor : public AMS_LevelScriptActorBase
{
	GENERATED_BODY()

public:
	AMS_TownLevelScriptActor();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Destroyed() override;

private:
	UFUNCTION()
	void OnPressDownEvent(FVector2D aPointerDownPosition, AActor* aPointerDownActor);
	UFUNCTION()
	void OnPressUpEvent(FVector2D aPointerUpPosition, AActor* aPointerUpActor);
};
