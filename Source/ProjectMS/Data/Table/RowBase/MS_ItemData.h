#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MS_ItemData.generated.h"

USTRUCT(BlueprintType) struct FMS_ItemData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	int32 ItemType = 0;
	UPROPERTY(EditAnywhere)
	FName ItemName = FName();
	UPROPERTY(EditAnywhere)
	int32 TemperatureType = 0;
	UPROPERTY(EditAnywhere)
	int32 Slot100x100MaxCount = 0;
	UPROPERTY(EditAnywhere)
	int32 BoxMaxCount = 0;
	UPROPERTY(EditAnywhere)
	int32 TakeMinCount = 0;
	UPROPERTY(EditAnywhere)
	int32 TakeMaxCount = 0;
	UPROPERTY(EditAnywhere)
	int32 PriceMin = 0;
	UPROPERTY(EditAnywhere)
	int32 PriceMax = 0;
	UPROPERTY(EditAnywhere)
	int32 PathFile = 0;
	UPROPERTY(EditAnywhere)
	int32 BoxMeshPath = 0;
	UPROPERTY(EditAnywhere)
	int32 SlotPath100x100 = 0;
	UPROPERTY(EditAnywhere)
	int32 ImagePath = 0;
};
