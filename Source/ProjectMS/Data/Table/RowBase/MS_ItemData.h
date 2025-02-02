#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MS_ItemData.generated.h"

USTRUCT(BlueprintType) struct FMS_ItemData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 StorageType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TemperatureType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	 int32 TakeMinCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	 int32 TakeMaxCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	 int32 Volume;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	 int32 PriceMin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	 int32 PriceMax;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	 UStaticMesh* StuffStaticMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	 UStaticMesh* StuffBundleStaticMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	 UStaticMesh* StuffBoxStaticMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	 int32 PathFile;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	 int32 ImagePath;
};
