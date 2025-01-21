#pragma once

#include "CoreMinimal.h"
#include "Actor/Prop/Furniture/Storage/Display/MS_DisplayStorage.h"
#include "MS_RefrigeratedDisplayStorage.generated.h"

UCLASS() class PROJECTMS_API AMS_RefrigeratedDisplayStorage : public AMS_DisplayStorage
{
	GENERATED_BODY()
	
public:
	AMS_RefrigeratedDisplayStorage(const FObjectInitializer& aObjectInitializer);

	virtual void PostInitializeComponents() override;
	
protected:
	virtual void BeginPlay() override;
};
