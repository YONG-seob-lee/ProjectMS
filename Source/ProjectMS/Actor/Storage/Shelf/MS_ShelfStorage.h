#pragma once

#include "CoreMinimal.h"
#include "Actor/Storage/MS_Storage.h"
#include "MS_ShelfStorage.generated.h"

UCLASS() class PROJECTMS_API AMS_ShlefStorage : public AMS_Storage
{
	GENERATED_BODY()

public:
	AMS_ShlefStorage();

	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float aDeltaTime) override;
};
