// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ContentsUtilities/MS_ItemDefine.h"
#include "MS_StackedBoxComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTMS_API UMS_StackedBoxComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	UMS_StackedBoxComponent();

protected:
	virtual void BeginPlay() override;
	
public:
	void OnChangeRequestSlotDatas(const TArray<FMS_SlotData>& aSlotDatas);
	void OnChangeCurrentSlotDatas(const TArray<FMS_SlotData>& aSlotDatas);

	void SetVisibility(bool bVisibility);

	void UpdateMesh();

	
protected:
	UPROPERTY(EditAnywhere)
	int32 BoxMeshId = 5001;

	UPROPERTY(EditAnywhere)
	TArray<FVector> BoxMeshLocations;
	
	UPROPERTY(Transient)
	TArray<FMS_SlotData> CacheSlotDatas;
	
	UPROPERTY(Transient)
	bool bCacheVisibility;

	UPROPERTY(Transient)
	int32 CacheBoxMeshNum;
};
