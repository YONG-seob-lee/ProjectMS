// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_LevelScriptActorBase.h"
#include "MS_StageLevelScriptActor.generated.h"

UCLASS()
class PROJECTMS_API AMS_StageLevelScriptActor : public AMS_LevelScriptActorBase
{
	GENERATED_BODY()

public:
	AMS_StageLevelScriptActor();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Destroyed() override;
private:
	UFUNCTION()
	void OnPressDownEvent(FVector2D aPointerDownPosition, const FHitResult& aInteractableHitResult);
	
	UFUNCTION()
	void OnPressUpEvent(FVector2D aPointerUpPosition, const FHitResult& aInteractableHitResult);
};
