// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Prop/MS_Prop.h"
#include "ContentsUtilities/MS_GameProcessDefine.h"
#include "MS_Furniture.generated.h"


UCLASS()
class PROJECTMS_API AMS_Furniture : public AMS_Prop
{
	GENERATED_BODY()

public:
	AMS_Furniture(const FObjectInitializer& aObjectInitializer);
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void PreInitializeComponents() override;
	virtual void PostInitializeComponents() override;

	
	// Select
	virtual void OnSelectProp(EMS_ModeState aModeState) override;
	virtual void OnUnselectProp(EMS_ModeState aModeState) override;

	
	// Slot Datas
	virtual void OnChangeRequestSlotDatas(const TArray<struct FMS_SlotData>& aSlotDatas);
	virtual void OnChangeCurrentSlotDatas(const TArray<struct FMS_SlotData>& aSlotDatas);

	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USceneComponent* SlotAttachedComponent;

	UPROPERTY()
	TMap<int32, TObjectPtr<class UMS_SlotChildActorComponent>> SlotIdToSlotComponents;
};
