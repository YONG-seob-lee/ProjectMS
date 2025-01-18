#pragma once

#include "CoreMinimal.h"
#include "Actor/Prop/Furniture/Storage/MS_Storage.h"
#include "MS_DisplayStorage.generated.h"

UCLASS() class PROJECTMS_API AMS_DisplayStorage : public AMS_Storage
{
	GENERATED_BODY()

public:
	AMS_DisplayStorage();

	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float aDeltaTime) override;
};
