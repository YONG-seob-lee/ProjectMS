// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_BasePathBPFile.generated.h"

    
USTRUCT()
struct FMS_BasePathBPFile: public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere)
	int32 Id = 0;
	UPROPERTY(EditAnywhere)
	int32 Directory_Table_Id = 0;
	UPROPERTY(EditAnywhere)
	FName BP_File_Name = FName();
};
