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
	int32 TemperatureType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Slot100x100MaxCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BoxMaxCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TakeMinCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TakeMaxCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 PriceMin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 PriceMax;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 PathFile;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BoxMeshPath;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SlotPath100x100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ImagePath;
};
