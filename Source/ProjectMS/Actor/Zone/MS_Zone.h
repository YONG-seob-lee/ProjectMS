// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Environment/MS_LevelPropDatas.h"
#include "MS_Zone.generated.h"

UCLASS()
class PROJECTMS_API AMS_Zone : public AActor
{
	GENERATED_BODY()

public:
	AMS_Zone();

	virtual void PostInitializeComponents() override;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;


private:
	void InitializeZoneData();
	
	void CreateGrids();


public:
	bool IsWorldGridContained(const FIntVector2& aInWorldGridPosition, FIntVector2& aOutZoneGridPosition) const;

	void RegisterFloorToGrid(const FIntVector2& aZoneGridPosition, TWeakObjectPtr<AActor> aFloor);
	void RegisterObjectToGrid(const FIntVector2& aZoneGridPosition, TWeakObjectPtr<AActor> aObject);


	// Setter
	void SetZoneIndex(int32 aZoneIndex) { ZoneIndex = aZoneIndex; }
	
	// Getter
	int32 GetZoneIndex() const { return ZoneIndex; }
	
	const FVector& GetZoneLocation() const { return ZoneLocation; }
	
	const FIntVector& GetZoneGridNum() const { return ZoneGridNum; }
	
	const FIntVector& GetZoneWorldGridPosition() const { return ZoneWorldGridPosition; }

	
protected:
	// Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* ZoneBoxComponent;


private:
	// Zone Data
	UPROPERTY()
	int32 ZoneIndex;
	
	UPROPERTY()
	FVector ZoneLocation;

	UPROPERTY()
	FIntVector ZoneGridNum;

	UPROPERTY()
	FIntVector ZoneWorldGridPosition;
	
	UPROPERTY()
	TMap<FIntVector2, FMS_GridData> Grids;
};
