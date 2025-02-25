#pragma once
#include "CoreMinimal.h"

#include "MS_Customer.generated.h"

/**
 * 
 */
USTRUCT()
struct FMS_Customer : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere)
	int32 ColorType = 0;
	
	UPROPERTY(EditAnywhere)
	int32 MaxItemKind = 0;

	UPROPERTY(EditAnywhere)
	int32 MaxItemCount = 0;

	UPROPERTY(EditAnywhere)
	int32 PathFile = 0;
};