// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_BasePathMeshFileCacheTable.h"

void UMS_BasePathMeshFileCacheTable::Initialize(TObjectPtr<UMS_TableManager> aMng)
{
	Super::Initialize(aMng);
	
	BuildTable(aMng, EMS_TableDataType::BasePathMeshFile, BasePathMeshFiles);

	HISMIds.Empty();
	for (auto& BasePathMeshFile : BasePathMeshFiles)
	{
		if (BasePathMeshFile.Value->HISM == true)
		{
			HISMIds.Emplace(BasePathMeshFile.Key);

			if (!BasePathMeshFile.Value->OverlayMaterial_File_Path.IsNone())
			{
				OverlapMaterialHISMIds.Emplace(BasePathMeshFile.Key);
			}
		}
	}
}

void UMS_BasePathMeshFileCacheTable::Finalize()
{
	Super::Finalize();
}
