#pragma once

#include "CoreMinimal.h"
#include "Actor/Prop/Furniture/Storage/Shelf/MS_ShelfStorage.h"
#include "MS_RefrigeratedShelfStorage.generated.h"

UCLASS() class PROJECTMS_API AMS_RefrigeratedShelfStorage : public AMS_ShelfStorage
{
	GENERATED_BODY()
	
public:
	AMS_RefrigeratedShelfStorage(const FObjectInitializer& aObjectInitializer);

	virtual void PostInitializeComponents() override;

protected:
	virtual void BeginPlay() override;
};
