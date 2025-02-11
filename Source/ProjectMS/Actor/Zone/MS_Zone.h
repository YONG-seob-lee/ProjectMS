// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_Actor.h"
#include "ContentsUtilities/MS_LevelDefine.h"
#include "MS_Zone.generated.h"

DECLARE_DELEGATE_OneParam(FMS_RequestOpenZoneDelegate, int32);

UCLASS()
class PROJECTMS_API AMS_Zone : public AMS_Actor
{
	GENERATED_BODY()

public:
	AMS_Zone(const FObjectInitializer& aObjectInitializer);

	virtual void PostInitializeComponents() override;

protected:
	virtual void BeginPlay() override;

private:
	void InitializeZoneData();
	
	void CreateGrids();

	void RegisterDefalutAttachedProps();


public:
	bool IsWorldLocationContained(const FVector& aInWorldLocation, FVector& aOutZoneLocation) const;
	bool IsGridContained(const FIntVector2& aInGridPosition) const;

	void RegisterFloorToGrid(const FIntVector2& aGridPosition, TWeakObjectPtr<class AMS_Floor> aFloor);
	void RegisterObjectToGrid(const FIntVector2& aGridPosition, TWeakObjectPtr<class UMS_PropSpaceComponent> aPropSpaceComponent);
	void UnregisterObjectToGrid(const FIntVector2& aGridPosition);

	// Zone Open
	UFUNCTION()
	void OnClickZoneOpenWidget(class UMS_ZoneOpenWidget* aZoneOpenWidget);
	
	void SetZoneOpened(bool aOpened) { bOpened = aOpened; }

	void OnZoneOpened();
	void OnAnyZoneOpened(TWeakObjectPtr<class AMS_ConstructibleLevelScriptActorBase> aOwnerLevelScriptActor);
	
	void SetWallVisibilities(TWeakObjectPtr<class AMS_ConstructibleLevelScriptActorBase> aOwnerLevelScriptActor);

	bool CanOpenZone();
	
	// Getter
	int32 GetZoneIndex() const { return ZoneIndex; }

	EMS_ZoneType GetZoneType() const { return ZoneType; }

	const TArray<int32>& GetTestConditionZoneIds() const { return TestConditionZoneIds; }
	
	const FVector& GetZoneLocation() const { return ZoneLocation; }
	
	const FIntVector2& GetZoneGridNum() const { return ZoneGridNum; }
	
	const FIntVector2& GetZoneWorldGridPosition() const { return ZoneWorldGridPosition; }

	const TMap<FIntVector2, FMS_GridData>& GetGrids() const { return Grids; }

	bool IsOpened() const { return bOpened; }
	
	const FMS_GridData* GetGrid(const FIntVector2& aGridPosition) const;

	void ShowDebugZoneData();

	
protected:
	// Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* ZoneBoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USceneComponent* FloorAttachedComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USceneComponent* WallAttachedComponent;

	// Widget Component
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UWidgetComponent> ZoneOpenWidgetComponent;


private:
	// Zone Data
	UPROPERTY(EditInstanceOnly, Category=MS_Zone)
	int32 ZoneIndex;
	
	UPROPERTY(EditInstanceOnly, Category=MS_Zone)
	EMS_ZoneType ZoneType;

	UPROPERTY(EditInstanceOnly, Category=MS_Zone)
	TArray<int32> TestConditionZoneIds;
	
	UPROPERTY()
	FVector ZoneLocation;

	UPROPERTY()
	FVector ZoneSize;
	
	UPROPERTY()
	FIntVector2 ZoneGridNum;

	UPROPERTY()
	FIntVector2 ZoneWorldGridPosition;

	UPROPERTY()
	bool bOpened;
	
	UPROPERTY()
	TMap<FIntVector2, FMS_GridData> Grids;

	UPROPERTY()
	TArray<TObjectPtr<class AMS_Wall>> Walls;

public:
	FMS_RequestOpenZoneDelegate RequestOpenZoneDelegate;
};
