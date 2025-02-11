// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ChildActorComponent.h"
#include "MS_SlotChildActorComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTMS_API UMS_SlotChildActorComponent : public UChildActorComponent
{
	GENERATED_BODY()

public:
	UMS_SlotChildActorComponent();

protected:
	virtual void BeginPlay() override;

public:
	// Property :: Getter
	int32 GetSlotOrder() const { return SlotOrder; }

	
protected:
	// Property
	UPROPERTY(EditAnywhere)
	int32 SlotOrder;
};
