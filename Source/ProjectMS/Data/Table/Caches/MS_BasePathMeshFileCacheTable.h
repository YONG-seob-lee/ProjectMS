// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Table/MS_CacheTable.h"
#include "Table/RowBase/MS_BasePathMeshFile.h"
#include "MS_BasePathMeshFileCacheTable.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_BasePathMeshFileCacheTable : public UMS_CacheTable
{
	GENERATED_BODY()
public:
	virtual void Initialize(TObjectPtr<UMS_TableManager> aMng) override;
	virtual void Finalize() override;

	const TArray<int32>& GetHISMIds() const { return HISMIds; }
	const TArray<int32>& GetOverlapMaterialHISMIds() const { return OverlapMaterialHISMIds; }

private:
	TMap<int32, FMS_BasePathMeshFile*> BasePathMeshFiles;
	TArray<int32> HISMIds;
	TArray<int32> OverlapMaterialHISMIds;
};
