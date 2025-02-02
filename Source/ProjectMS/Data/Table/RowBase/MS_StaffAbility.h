#pragma once

#include "CoreMinimal.h"
#include "MS_StaffAbility.generated.h"

/**
 * 
 */
USTRUCT()
struct FMS_StaffAbility : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	int32 StaffId = 0;
	UPROPERTY(EditAnywhere)
	int32 Work = 0;
	UPROPERTY(EditAnywhere)
	int32 Endurance = 0;
	UPROPERTY(EditAnywhere)
	int32 Diligence = 0;
	UPROPERTY(EditAnywhere)
	int32 Kindness = 0;
	UPROPERTY(EditAnywhere)
	int32 Plannedness = 0;
};
