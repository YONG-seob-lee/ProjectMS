// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MS_HISMManager.generated.h"

namespace MeshName
{
	const FName FloorA = TEXT("FloorA");
	const FName FloorB = TEXT("FloorB");
	const FName OutsideFloorA = TEXT("OutsideFloorA");
	const FName WallA = TEXT("WallA");
	
	const TMap<FName, const TCHAR*> NameToMeshPath = {
		{MeshName::FloorA, TEXT("/Game/3D/StaticMesh/SM_CON_FLOOR_50A.SM_CON_FLOOR_50A")}
		, {MeshName::FloorB, TEXT("/Game/3D/StaticMesh/SM_CON_FLOOR_50B.SM_CON_FLOOR_50B")}
		, {MeshName::WallA, TEXT("/Game/3D/StaticMesh/SM_CON_WALL_50A.SM_CON_WALL_50A")}
		, {MeshName::OutsideFloorA, TEXT("/Game/3D/StaticMesh/SM_CON_FLOOR_50A.SM_CON_FLOOR_50A")}
	};

	const TMap<FName, const TCHAR*> NameToMaterialPath = {
		{MeshName::OutsideFloorA, TEXT("/Game/3D/Material/MI_atlas_03.MI_atlas_03")}
	};
}


UCLASS()
class PROJECTMS_API AMS_HISMManager : public AActor
{
	GENERATED_BODY()

public:
	AMS_HISMManager();

	static AMS_HISMManager* GetInstance();
	
protected:
	virtual void BeginPlay() override;

public:
	void Initialize();
	
	void AddInstance(const FName& aMeshName, const FTransform& aTransform);
	void AddInstances(const FName& aMeshName, const TArray<FTransform>& aTransforms);

	bool RemoveInstance(const FName& aMeshName, const FVector& aLocation);
	bool RemoveInstances(const FName& aMeshName, const TArray<FVector>& aLocations);
	
	void ClearInstances();

private:
	void RebuildInstanceIds(const FName& aMeshName);

	
private:
	TMap<FName, TObjectPtr<class UHierarchicalInstancedStaticMeshComponent>> MeshNameToHISM;

	TMap<FName, TMap<FVector, int32>> MeshLocationToInstanceIds;
	
	// Instance
	inline static TObjectPtr<AMS_HISMManager> HISMManager = nullptr;
	
#define gHISMMng (*AMS_HISMManager::GetInstance())
};
