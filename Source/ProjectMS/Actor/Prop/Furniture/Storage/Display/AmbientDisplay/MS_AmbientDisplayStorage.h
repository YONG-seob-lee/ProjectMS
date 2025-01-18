#pragma once

#include "CoreMinimal.h"
#include "Actor/Prop/Furniture/Storage/Display/MS_DisplayStorage.h"
#include "MS_AmbientDisplayStorage.generated.h"

UCLASS() class PROJECTMS_API AMS_AmbientDisplayStorage : public AMS_DisplayStorage
{
	GENERATED_BODY()

public:
	AMS_AmbientDisplayStorage();

	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float aDeltaTime) override;
};
