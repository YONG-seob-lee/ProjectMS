#pragma once

#include "CoreMinimal.h"
#include "Actor/Prop/Furniture/Storage/MS_Storage.h"
#include "MS_ShelfStorage.generated.h"

UCLASS() class PROJECTMS_API AMS_ShelfStorage : public AMS_Storage
{
	GENERATED_BODY()

public:
	AMS_ShelfStorage(const FObjectInitializer& aObjectInitializer);

	virtual void PostInitializeComponents() override;

protected:
	virtual void BeginPlay() override;
};
