// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_ActorBase.h"
#include "MS_Item.generated.h"

UCLASS()
class PROJECTMS_API AMS_Item : public AMS_ActorBase
{
	GENERATED_BODY()

public:
	AMS_Item(const FObjectInitializer& aObjectInitializer);

protected:
	virtual void BeginPlay() override;

public:
	void SetItemVisibility(bool bVisibility);

	
protected:
	// Component
	UPROPERTY(EditAnywhere)
	UMeshComponent* MeshComponent;
};
