#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MS_Item.generated.h"

USTRUCT(BlueprintType) struct FMS_Item : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite) Undefined ItemType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) Undefined ItemName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) Undefined TemperatureType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) Undefined TakeMinCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) Undefined TakeMaxCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) Undefined Volume;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) Undefined PriceMin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) Undefined PriceMax;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) Undefined Model;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) Undefined PathFile;
};