// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_HISMManager.h"

#include "MS_Define.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"


AMS_HISMManager::AMS_HISMManager()
{
	PrimaryActorTick.bCanEverTick = false;
	
	HISMManager = this;

	for (auto& It : MeshName::MeshNameToPath)
	{
		UHierarchicalInstancedStaticMeshComponent* Component = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(It.Key);
		if (Component)
		{
			if(UStaticMesh* Mesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, It.Value)))
			{
				Component->SetStaticMesh(Mesh);
			}
			else
			{
				MS_ENSURE(false);
			}

			MeshNameToHISM.Emplace(It.Key, Component);
			MeshLocationToInstanceIds.Emplace(It.Key);
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

void AMS_HISMManager::AddInstance(const FName& aMeshName, const FTransform& aTransform)
{
	if (!MeshNameToHISM.Contains(aMeshName))
	{
		MS_ENSURE(false);
		return;
	}

	TObjectPtr<UHierarchicalInstancedStaticMeshComponent> HISM = *MeshNameToHISM.Find(aMeshName);
	if (HISM)
	{
		TMap<FVector, int32>* pMap = MeshLocationToInstanceIds.Find(aMeshName);
		if (pMap == nullptr)
		{
			MS_ENSURE(false);
			return;
		}
		
		int32 Id = HISM->AddInstance(aTransform, true);
		pMap->Emplace(aTransform.GetLocation(), Id);
	}
}

void AMS_HISMManager::AddInstances(const FName& aMeshName, const TArray<FTransform>& aTransforms)
{
	if (!MeshNameToHISM.Contains(aMeshName))
	{
		MS_ENSURE(false);
		return;
	}

	TObjectPtr<UHierarchicalInstancedStaticMeshComponent> HISM = *MeshNameToHISM.Find(aMeshName);
	if (HISM)
	{
		TMap<FVector, int32>* pMap = MeshLocationToInstanceIds.Find(aMeshName);
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
				pMap->Emplace(aTransforms[i].GetLocation(), Ids[i]);
			}
		}
	}
}

bool AMS_HISMManager::RemoveInstance(const FName& aMeshName, const FVector& aLocation)
{
	if (!MeshNameToHISM.Contains(aMeshName))
	{
		MS_ENSURE(false);
		return false;
	}

	TObjectPtr<UHierarchicalInstancedStaticMeshComponent> HISM = *MeshNameToHISM.Find(aMeshName);
	if (HISM)
	{
		TMap<FVector, int32>* pMap = MeshLocationToInstanceIds.Find(aMeshName);
		if (pMap == nullptr)
		{
			MS_ENSURE(false);
			return false;
		}
		
		if (pMap->Contains(aLocation))
		{
			int32 Id = *pMap->Find(aLocation);
			if (HISM->RemoveInstance(Id))
			{
				RebuildInstanceIds(aMeshName);
				return true;
			}
		}
	}

	return false;
}

bool AMS_HISMManager::RemoveInstances(const FName& aMeshName, const TArray<FVector>& aLocations)
{
	if (!MeshNameToHISM.Contains(aMeshName))
	{
		MS_ENSURE(false);
		return false;
	}

	TObjectPtr<UHierarchicalInstancedStaticMeshComponent> HISM = *MeshNameToHISM.Find(aMeshName);
	if (HISM)
	{
		TMap<FVector, int32>* pMap = MeshLocationToInstanceIds.Find(aMeshName);
		if (pMap == nullptr)
		{
			MS_ENSURE(false);
			return false;
		}

		TArray<int32> Ids;
		for (const FVector& Location : aLocations)
		{
			if (pMap->Contains(Location))
			{
				Ids.Emplace(*pMap->Find(Location));
			}
		}
		
		if (HISM->RemoveInstances(Ids))
		{
			RebuildInstanceIds(aMeshName);
			return true;
		}
	}

	return false;
}

void AMS_HISMManager::ClearInstances()
{
	for (auto& It : MeshNameToHISM)
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

void AMS_HISMManager::RebuildInstanceIds(const FName& aMeshName)
{
	if (!MeshNameToHISM.Contains(aMeshName))
	{
		MS_ENSURE(false);
		return;
	}

	TObjectPtr<UHierarchicalInstancedStaticMeshComponent> HISM = *MeshNameToHISM.Find(aMeshName);
	if (HISM)
	{
		TMap<FVector, int32>* pMap = MeshLocationToInstanceIds.Find(aMeshName);
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
			pMap->Emplace(Transform.GetLocation(), i);
		}
	}
}
