

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MS_MenuElement.generated.h"

/**
 * 
 */
USTRUCT()
struct FMS_MenuElement : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere)
	int32 ImagePath = 0;
	UPROPERTY(EditAnywhere)
	FString ElementName = FString();
	
};
