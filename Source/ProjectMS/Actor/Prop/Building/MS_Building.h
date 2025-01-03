// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Prop/MS_Prop.h"
#include "MS_Building.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class PROJECTMS_API AMS_Building : public AMS_Prop
{
	GENERATED_BODY()
public:
	AMS_Building();
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	virtual bool HasInteractionComponent() override;
	virtual void OnPressDownEvent() override;
	virtual void OnPressUpEvent() override;
	virtual void LaunchEvent() override;
	
private:
	void UpdateFloorSize();
	void SetFloor(int32 aFloor);
	
	UPROPERTY(EditAnywhere, Category = "Floor", meta = (AllowPrivateAccess = "true"))
	int32 Floor = 0;
	
	UPROPERTY(BlueprintReadOnly, Category = "Floor", meta = (AllowPrivateAccess = "true"))
	float MiddleStartLocationZ = 0.f;

	UPROPERTY(BlueprintReadOnly, Category = "Floor", meta = (AllowPrivateAccess = "true"))
	float MiddleSizeZ = 0.f;
	
	UPROPERTY(EditAnywhere, Category = "Floor", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> BuildingFront = nullptr;

	UPROPERTY(EditAnywhere, Category = "Floor", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> BuildingMiddle = nullptr;

	UPROPERTY(EditAnywhere, Category = "Floor", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> BuildingRear = nullptr;
	
	UPROPERTY()
	TArray<TObjectPtr<UStaticMeshComponent>> MiddleArray;
	
	UPROPERTY(EditAnywhere, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UMS_InteractionComponent> InteractionComponent = nullptr;
};