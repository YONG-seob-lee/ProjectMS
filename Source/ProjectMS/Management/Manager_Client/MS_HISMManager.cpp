// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_HISMManager.h"

#include "MS_Define.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Table/Caches/MS_BasePathMeshFileCacheTable.h"


AMS_HISMManager::AMS_HISMManager()
{
	PrimaryActorTick.bCanEverTick = false;
	
	HISMManager = this;

	if (const TObjectPtr TableManager = gTableMng)
	{
		const TObjectPtr<UMS_BasePathMeshFileCacheTable> MeshPathCacheTable = Cast<UMS_BasePathMeshFileCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::BasePathMeshFile));
		MS_ENSURE(MeshPathCacheTable);

		const TArray<int32>& HISMIds = MeshPathCacheTable->GetHISMIds();
	
		for (int32 Id : HISMIds)
		{
			UHierarchicalInstancedStaticMeshComponent* pHISMComponent = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>
				(FName(FString("HISM") + FString::FromInt(Id)));
		
			if (pHISMComponent)
			{
				const FString MeshPath = gTableMng.GetPath(EMS_TableDataType::BasePathMeshFile, Id);
			
				if(UStaticMesh* Mesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, *MeshPath)))
				{
					pHISMComponent->SetStaticMesh(Mesh);
				}
				else
				{
					MS_ENSURE(false);
				}

				MeshTableIdToHISM.Emplace(Id, pHISMComponent);
				MeshLocationToInstanceIds.Emplace(Id);
			}
		}

		const TArray<int32>& OverlapMaterialHISMIds = MeshPathCacheTable->GetOverlapMaterialHISMIds();
		
		for (int32 Id : OverlapMaterialHISMIds)
		{
			const FString MaterialPath = gTableMng.GetPath(EMS_TableDataType::BasePathMeshFile, Id, false, 1);

			if (!MaterialPath.IsEmpty())
			{
				TObjectPtr<UHierarchicalInstancedStaticMeshComponent>* ppHISMComponent = MeshTableIdToHISM.Find(Id);
				if (ppHISMComponent != nullptr)
				{
					TObjectPtr<UHierarchicalInstancedStaticMeshComponent> pHISMComponent = *ppHISMComponent;

					if(UMaterialInterface* Material = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr, *MaterialPath)))
					{
						pHISMComponent->SetOverlayMaterial(Material);
					}
					else
					{
						MS_ENSURE(false);
					}
				}
			}
		}
	}
}

AMS_HISMManager* AMS_HISMManager::GetInstance()
{
	return HISMManager;
}

void AMS_HISMManager::BeginPlay()
{
	Super::BeginPlay();
}

void AMS_HISMManager::Initialize()
{
}

void AMS_HISMManager::AddInstance(int32 aMeshId, const FTransform& aTransform)
{
	if (!MeshTableIdToHISM.Contains(aMeshId))
	{
		MS_ENSURE(false);
		return;
	}

	TObjectPtr<UHierarchicalInstancedStaticMeshComponent> HISM = *MeshTableIdToHISM.Find(aMeshId);
	if (HISM)
	{
		TMap<FIntVector, int32>* pMap = MeshLocationToInstanceIds.Find(aMeshId);
		if (pMap == nullptr)
		{
			MS_ENSURE(false);
			return;
		}
		
		int32 Id = HISM->AddInstance(aTransform, true);
		pMap->Emplace(ConvertLocationToHISMKey(aTransform.GetLocation()), Id);
	}
}

void AMS_HISMManager::AddInstances(int32 aMeshId, const TArray<FTransform>& aTransforms)
{
	if (!MeshTableIdToHISM.Contains(aMeshId))
	{
		MS_ENSURE(false);
		return;
	}

	TObjectPtr<UHierarchicalInstancedStaticMeshComponent> HISM = *MeshTableIdToHISM.Find(aMeshId);
	if (HISM)
	{
		TMap<FIntVector, int32>* pMap = MeshLocationToInstanceIds.Find(aMeshId);
		if (pMap == nullptr)
		{
			MS_ENSURE(false);
			return;
		}
		
		TArray<int32> Ids = HISM->AddInstances(aTransforms, true, true);
		
		for (int32 i = 0; i < aTransforms.Num() - 1; ++i)
		{
			if (Ids.IsValidIndex(i))
			{
				pMap->Emplace(ConvertLocationToHISMKey(aTransforms[i].GetLocation()), Ids[i]);
			}
		}
	}
}

bool AMS_HISMManager::RemoveInstance(int32 aMeshId, const FVector& aLocation)
{
	if (!MeshTableIdToHISM.Contains(aMeshId))
	{
		MS_ENSURE(false);
		return false;
	}

	TObjectPtr<UHierarchicalInstancedStaticMeshComponent> HISM = *MeshTableIdToHISM.Find(aMeshId);
	if (HISM)
	{
		FIntVector Key = ConvertLocationToHISMKey(aLocation);
		
		TMap<FIntVector, int32>* pMap = MeshLocationToInstanceIds.Find(aMeshId);
		if (pMap == nullptr)
		{
			MS_ENSURE(false);
			return false;
		}
		
		if (pMap->Contains(Key))
		{
			int32 Id = *pMap->Find(Key);
			if (HISM->RemoveInstance(Id))
			{
				RebuildInstanceIds(aMeshId);
				return true;
			}
		}
	}

	return false;
}

bool AMS_HISMManager::RemoveInstances(int32 aMeshId, const TArray<FVector>& aLocations)
{
	if (!MeshTableIdToHISM.Contains(aMeshId))
	{
		MS_ENSURE(false);
		return false;
	}

	TObjectPtr<UHierarchicalInstancedStaticMeshComponent> HISM = *MeshTableIdToHISM.Find(aMeshId);
	if (HISM)
	{
		TMap<FIntVector, int32>* pMap = MeshLocationToInstanceIds.Find(aMeshId);
		if (pMap == nullptr)
		{
			MS_ENSURE(false);
			return false;
		}

		TArray<int32> Ids;
		for (const FVector& Location : aLocations)
		{
			FIntVector Key = ConvertLocationToHISMKey(Location);
			
			if (pMap->Contains(Key))
			{
				Ids.Emplace(*pMap->Find(Key));
			}
		}
		
		if (HISM->RemoveInstances(Ids))
		{
			RebuildInstanceIds(aMeshId);
			return true;
		}
	}

	return false;
}

void AMS_HISMManager::ClearInstances()
{
	for (auto& It : MeshTableIdToHISM)
	{
		if (It.Value)
		{
			It.Value->ClearInstances();
		}
	}

	for (auto& It : MeshLocationToInstanceIds)
	{
		It.Value.Empty();
	}
}

void AMS_HISMManager::RebuildInstanceIds(int32 aMeshId)
{
	if (!MeshTableIdToHISM.Contains(aMeshId))
	{
		MS_ENSURE(false);
		return;
	}

	TObjectPtr<UHierarchicalInstancedStaticMeshComponent> HISM = *MeshTableIdToHISM.Find(aMeshId);
	if (HISM)
	{
		TMap<FIntVector, int32>* pMap = MeshLocationToInstanceIds.Find(aMeshId);
		if (pMap == nullptr)
		{
			MS_ENSURE(false);
			return;
		}
		
		pMap->Empty();
		
		for (int32 i = 0; i < HISM->GetInstanceCount(); ++i)
		{
			FTransform Transform = FTransform();
			HISM->GetInstanceTransform(i, Transform, true);
			pMap->Emplace(ConvertLocationToHISMKey(Transform.GetLocation()), i);
		}
	}
}

FIntVector AMS_HISMManager::ConvertLocationToHISMKey(const FVector& aLocation)
{
	return FIntVector(FMath::FloorToInt32(aLocation.X), FMath::FloorToInt32(aLocation.Y), FMath::FloorToInt32(aLocation.Z));
}
