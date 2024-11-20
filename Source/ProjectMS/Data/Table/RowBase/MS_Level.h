#pragma once
    
#include "CoreMinimal.h"
#include "MS_Level.generated.h"
    
USTRUCT()
struct FMS_Level: public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere)
	int32 Index = 0;
	UPROPERTY(EditAnywhere)
	FName LevelName = FName();
	UPROPERTY(EditAnywhere)
	int32 LevelKey = 0;
	UPROPERTY(EditAnywhere)
	FName PrimitiveWidgetName = FName();
};