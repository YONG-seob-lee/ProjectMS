#pragma once

#include "CoreMinimal.h"
#include "MS_Tutorial.generated.h"

/**
 * 
 */
USTRUCT()
struct FMS_Tutorial : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	FString Name = FString();
	
	UPROPERTY(EditAnywhere)
	FString Desc = FString();

	UPROPERTY(EditAnywhere)
	FString SubDesc = FString();
};