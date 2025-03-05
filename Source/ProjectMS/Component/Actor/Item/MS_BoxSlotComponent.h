// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ContentsUtilities/MS_ItemDefine.h"
#include "MS_BoxSlotComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTMS_API UMS_BoxSlotComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	UMS_BoxSlotComponent();

protected:
	virtual void BeginPlay() override;
	
public:
	int32 GetSlotId() const { return SlotId; }

	void OnChangeRequestSlotData(const FMS_SlotData& aSlotDatas);
	void OnChangeCurrentSlotData(const FMS_SlotData& aSlotDatas);

	void SetVisibility(bool bVisibility);

	void UpdateMesh();

	
protected:
	UPROPERTY(EditAnywhere)
	int32 SlotId;
	
	UPROPERTY(Transient)
	FMS_SlotData CacheSlotData;

	UPROPERTY(Transient)
	bool bCacheVisibility;

	UPROPERTY(EditAnywhere)
	bool bHaveMash;
};