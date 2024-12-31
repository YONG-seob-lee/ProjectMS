// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MS_InteractionComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTMS_API UMS_InteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UMS_InteractionComponent();

	virtual void BeginPlay() override;
	virtual void PostLoad() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void OnPressedEvent();
	void OnReleasedEvent();
	
private:
	void SetOnReleasedFinished();
	
	TWeakObjectPtr<AActor> Actor = nullptr;
	FVector DefaultScale = FVector(-1.5f, -1.f, -1.f);
	FTimerHandle OnPressedFinishedHandle;
	FTimerHandle OnReleasedFinishedHandle;
};
