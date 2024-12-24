#pragma once

#include "CoreMinimal.h"
#include "Actor/Storage/Display/MS_DisplayStorage.h"
#include "MS_RefrigeratedDisplayStorage.generated.h"

UCLASS() class PROJECTMS_API AMS_RefrigeratedDisplayStorage : public AMS_DisplayStorage
{
	GENERATED_BODY()
	
public:
	AMS_RefrigeratedDisplayStorage();

	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float aDeltaTime) override;
};
