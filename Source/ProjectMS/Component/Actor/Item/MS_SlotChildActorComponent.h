// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ChildActorComponent.h"
#include "ContentsUtilities/MS_ItemDefine.h"
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

	void OnChangeRequestSlotData(const FMS_SlotData& aSlotDatas);
	void OnChangeCurrentSlotData(const FMS_SlotData& aSlotDatas);

	
protected:
	// Property
	UPROPERTY(EditAnywhere)
	int32 SlotOrder;

	UPROPERTY(Transient)
	FMS_SlotData CacheSlotData;
};
