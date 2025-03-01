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

int32 AMS_HISMManager::AddInstance(const FName& aMeshName, const FTransform& aTransform)
{
	if (!MeshNameToHISM.Contains(aMeshName))
	{
		MS_ENSURE(false);
	}

	TObjectPtr<UHierarchicalInstancedStaticMeshComponent> HISM = *MeshNameToHISM.Find(aMeshName);
	if (HISM)
	{
		return HISM->AddInstance(aTransform, true);
	}

	return INDEX_NONE;
}

TArray<int32> AMS_HISMManager::AddInstances(const FName& aMeshName, const TArray<FTransform>& aTransforms)
{
	if (!MeshNameToHISM.Contains(aMeshName))
	{
		MS_ENSURE(false);
	}

	TObjectPtr<UHierarchicalInstancedStaticMeshComponent> HISM = *MeshNameToHISM.Find(aMeshName);
	if (HISM)
	{
		return HISM->AddInstances(aTransforms, true, true);
	}

	return TArray<int32>();
}

bool AMS_HISMManager::RemoveInstance(const FName& aMeshName, int32 aId)
{
	if (!MeshNameToHISM.Contains(aMeshName))
	{
		MS_ENSURE(false);
	}

	TObjectPtr<UHierarchicalInstancedStaticMeshComponent> HISM = *MeshNameToHISM.Find(aMeshName);
	if (HISM)
	{
		return HISM->RemoveInstance(aId);
	}

	return false;
}

bool AMS_HISMManager::RemoveInstances(const FName& aMeshName, const TArray<int32>& aIds)
{
	if (!MeshNameToHISM.Contains(aMeshName))
	{
		MS_ENSURE(false);
	}

	TObjectPtr<UHierarchicalInstancedStaticMeshComponent> HISM = *MeshNameToHISM.Find(aMeshName);
	if (HISM)
	{
		return HISM->RemoveInstances(aIds);
	}

	return false;
}

bool AMS_HISMManager::HideInstance(const FName& aMeshName, int32 aId)
{
	if (!MeshNameToHISM.Contains(aMeshName))
	{
		MS_ENSURE(false);
	}

	TObjectPtr<UHierarchicalInstancedStaticMeshComponent> HISM = *MeshNameToHISM.Find(aMeshName);
	if (HISM)
	{
		static const FTransform TransformForHide = FTransform(FVector(0.f, 0.f, -9999.f));
		return HISM->UpdateInstanceTransform(aId, TransformForHide, true, true);
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
}
