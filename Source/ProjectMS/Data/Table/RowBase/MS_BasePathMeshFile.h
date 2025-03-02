// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_BasePathMeshFile.generated.h"

USTRUCT()
struct FMS_BasePathMeshFile: public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere)
	int32 Directory_Table_Id = 0;
	UPROPERTY(EditAnywhere)
	FName Mesh_File_Name = FName();
	UPROPERTY(EditAnywhere)
	int32 OverlayMaterial_Directory_Table_Id = 0;
	UPROPERTY(EditAnywhere)
	FName OverlayMaterial_File_Path = FName();
	UPROPERTY(EditAnywhere)
	bool HISM = false;
};