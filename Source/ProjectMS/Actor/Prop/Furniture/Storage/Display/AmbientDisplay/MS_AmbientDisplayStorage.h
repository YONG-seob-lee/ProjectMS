#pragma once

#include "CoreMinimal.h"
#include "Actor/Prop/Furniture/Storage/Display/MS_DisplayStorage.h"
#include "MS_AmbientDisplayStorage.generated.h"

UCLASS() class PROJECTMS_API AMS_AmbientDisplayStorage : public AMS_DisplayStorage
{
	GENERATED_BODY()

public:
	AMS_AmbientDisplayStorage(const FObjectInitializer& aObjectInitializer);

	virtual void PostInitializeComponents() override;
	
protected:
	virtual void BeginPlay() override;
};
