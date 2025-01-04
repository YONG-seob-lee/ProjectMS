#pragma once
    
#include "CoreMinimal.h"
#include "MS_ResourceWidget.generated.h"
    
USTRUCT()
struct FMS_ResourceWidget: public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere)
	int32 Id = 0;
	UPROPERTY(EditAnywhere)
	FName TypeName = FName();
	UPROPERTY(EditAnywhere)
	int32 zOrder = 0;
	UPROPERTY(EditAnywhere)
	int32 Path_File = 0;
	UPROPERTY(EditAnywhere)
	bool NotRender3D = false;
	UPROPERTY(EditAnywhere)
	int32 ExclusiveGroup = 0;
};
