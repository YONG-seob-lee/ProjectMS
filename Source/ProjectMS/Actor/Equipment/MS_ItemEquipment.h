// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_Equipment.h"
#include "MS_ItemEquipment.generated.h"

UCLASS()
class PROJECTMS_API AMS_ItemEquipment : public AMS_Equipment
{
	GENERATED_BODY()

public:
	AMS_ItemEquipment(const FObjectInitializer& aObjectInitializer);

	void SetMesh(const TObjectPtr<UStaticMesh>* StaticMesh) const;
protected:
	virtual void BeginPlay() override;
};
