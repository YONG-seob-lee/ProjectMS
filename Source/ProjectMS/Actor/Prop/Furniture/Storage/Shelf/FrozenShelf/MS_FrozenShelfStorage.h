#pragma once

#include "CoreMinimal.h"
#include "Actor/Prop/Furniture/Storage/Shelf/MS_ShelfStorage.h"
#include "MS_FrozenShelfStorage.generated.h"

UCLASS() class PROJECTMS_API AMS_FrozenShelfStorage : public AMS_ShelfStorage
{
	GENERATED_BODY()
	
public:
	AMS_FrozenShelfStorage(const FObjectInitializer& aObjectInitializer);

	virtual void PostInitializeComponents() override;
	
protected:
	virtual void BeginPlay() override;
};
