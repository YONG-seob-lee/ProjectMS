// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MS_HISMManager.generated.h"


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
	
	void AddInstance(int32 aMeshId, const FTransform& aTransform);
	void AddInstances(int32 aMeshId, const TArray<FTransform>& aTransforms);

	bool RemoveInstance(int32 aMeshId, const FVector& aLocation);
	bool RemoveInstances(int32 aMeshId, const TArray<FVector>& aLocations);
	
	void ClearInstances();

private:
	void RebuildInstanceIds(int32 aMeshId);

	static FIntVector ConvertLocationToHISMKey(const FVector& aLocation);

	
private:
	TMap<int32, TObjectPtr<class UHierarchicalInstancedStaticMeshComponent>> MeshTableIdToHISM;

	TMap<int32, TMap<FIntVector, int32>> MeshLocationToInstanceIds;
	
	// Instance
	inline static TObjectPtr<AMS_HISMManager> HISMManager = nullptr;
	
#define gHISMMng (*AMS_HISMManager::GetInstance())
};
