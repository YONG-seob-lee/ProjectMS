// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ChildActorComponent.h"
#include "ContentsUtilities/MS_ItemDefine.h"
#include "MS_ItemSlotChildActorComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTMS_API UMS_ItemSlotChildActorComponent : public UChildActorComponent
{
	GENERATED_BODY()

public:
	UMS_ItemSlotChildActorComponent();

protected:
	virtual void BeginPlay() override;

public:
	int32 GetSlotId() const { return SlotId; }

	void OnChangeRequestSlotData(const FMS_SlotData& aSlotData);
	void OnChangeCurrentSlotData(const FMS_SlotData& aSlotData);

	void SetVisibility(bool bVisibility);

	
protected:
	UPROPERTY(EditAnywhere)
	int32 SlotId;
	
	UPROPERTY(Transient)
	FMS_SlotData CacheSlotData;

	UPROPERTY(Transient)
	bool bCacheVisibility;
};
