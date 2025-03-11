#pragma once

#include "CoreMinimal.h"
#include "MS_Staff.generated.h"

/**
 * 
 */
USTRUCT()
struct FMS_Staff : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	FString StaffNameLocalKey = FString();
	UPROPERTY(EditAnywhere)
	int32 Color = 0;
	UPROPERTY(EditAnywhere)
	int32 Gender = 0;
	UPROPERTY(EditAnywhere)
	int32 Age = 0;
	UPROPERTY(EditAnywhere)
	int32 MBTI = 0;
	UPROPERTY(EditAnywhere)
	int32 RequiredSalaryMax = 0;
	UPROPERTY(EditAnywhere)
	int32 RequiredSalaryMin = 0;
	UPROPERTY(EditAnywhere)
	int32 SlotCount = 0;
	UPROPERTY(EditAnywhere)
	int32 PortraitPath = 0;
	UPROPERTY(EditAnywhere)
	int32 PathFile = 0;
	UPROPERTY(EditAnywhere)
	bool PreSpawned = false;
};
