#pragma once

#include "CoreMinimal.h"
#include "Actor/Storage/Shelf/MS_ShelfStorage.h"
#include "MS_RefrigeratedShelfStorage.generated.h"

UCLASS() class PROJECTMS_API AMS_RefrigeratedShelfStorage : public AMS_ShelfStorage
{
	GENERATED_BODY()
	
public:
	AMS_RefrigeratedShelfStorage();

	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float aDeltaTime) override;
};
