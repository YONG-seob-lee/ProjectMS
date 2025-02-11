// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ChildActorComponent.h"
#include "MS_ItemChildActorComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTMS_API UMS_ItemChildActorComponent : public UChildActorComponent
{
	GENERATED_BODY()

public:
	UMS_ItemChildActorComponent();

protected:
	virtual void BeginPlay() override;

public:
	int32 GetItemOrder() const { return ItemOrder; }

	void SetItemVisibility(bool bVisibility);

	
protected:
	UPROPERTY(EditAnywhere)
	int32 ItemOrder;
};
