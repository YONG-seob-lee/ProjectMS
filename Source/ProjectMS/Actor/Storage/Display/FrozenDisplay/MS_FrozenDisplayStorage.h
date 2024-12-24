#pragma once

#include "CoreMinimal.h"
#include "Actor/Storage/Display/MS_DisplayStorage.h"
#include "MS_FrozenDisplayStorage.generated.h"

UCLASS()
class PROJECTMS_API AMS_FrozenDisplayStorage : public AMS_DisplayStorage
{
	GENERATED_BODY()
	
public:
	AMS_FrozenDisplayStorage();

	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float aDeltaTime) override;
};
