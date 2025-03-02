// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_Actor.h"
#include "ContentsUtilities/MS_ItemDefine.h"
#include "MS_SlotActor.generated.h"

UCLASS()
class PROJECTMS_API AMS_SlotActor : public AMS_Actor
{
	GENERATED_BODY()

public:
	AMS_SlotActor(const FObjectInitializer& aObjectInitializer);

protected:
	virtual void BeginPlay() override;

public:
	virtual void PreInitializeComponents() override;
	virtual void PostInitializeComponents() override;

	
	void OnChangeCurrentSlotData(const FMS_SlotData& aSlotData);

	void SetVisibility(bool bVisibility);
	
	void UpdateMeshes(FMS_SlotData aSlotDatas, bool bRemoveAll);

	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* ItemAttachedComponent;

	UPROPERTY()
	TMap<int32, TObjectPtr<class UMS_MeshTransformComponent>> MeshTransformComponents;

	UPROPERTY(Transient)
	FMS_SlotData CacheSlotData;
	
	UPROPERTY(Transient)
	int32 CacheMeshId;

	UPROPERTY(Transient)
	bool bCacheVisibility;
};
