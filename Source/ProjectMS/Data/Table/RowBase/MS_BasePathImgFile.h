// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MS_BasePathImgFile.generated.h"
    
USTRUCT()
struct FMS_BasePathImgFile: public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere)
	int32 Directory_Table_Id = 0;
	UPROPERTY(EditAnywhere)
	FString Img_File_Name = FString();
	UPROPERTY(EditAnywhere)
	bool Img_File_Local = false;
};
