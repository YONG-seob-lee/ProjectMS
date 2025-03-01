// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MS_HISMManager.generated.h"

namespace MeshName
{
	const FName FloorA = TEXT("FloorA");
	const FName FloorB = TEXT("FloorB");
	const FName WallA = TEXT("WallA");
	
	const TMap<FName, const TCHAR*> MeshNameToPath
	= {{MeshName::FloorA, TEXT("/Game/3D/StaticMesh/SM_CON_FLOOR_50A.SM_CON_FLOOR_50A")}
		, {MeshName::FloorB, TEXT("/Game/3D/StaticMesh/SM_CON_FLOOR_50B.SM_CON_FLOOR_50B")}
		, {MeshName::WallA, TEXT("/Game/3D/StaticMesh/SM_CON_WALL_50A.SM_CON_WALL_50A")}};
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
	
	int32 AddInstance(const FName& aMeshName, const FTransform& aTransform);
	TArray<int32> AddInstances(const FName& aMeshName, const TArray<FTransform>& aTransforms);

	bool RemoveInstance(const FName& aMeshName, int32 aId);
	bool RemoveInstances(const FName& aMeshName, const TArray<int32>& aIds);

	bool HideInstance(const FName& aMeshName, int32 aId);

	void ClearInstances();

private:
	TMap<FName, TObjectPtr<class UHierarchicalInstancedStaticMeshComponent>> MeshNameToHISM;
	
	// Instance
	inline static TObjectPtr<AMS_HISMManager> HISMManager = nullptr;
	
#define gHISMMng (*AMS_HISMManager::GetInstance())
};
