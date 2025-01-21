#pragma once

#include "CoreMinimal.h"
#include "Actor/Prop/Furniture/Storage/Shelf/MS_ShelfStorage.h"
#include "MS_AmbientShelfStorage.generated.h"

UCLASS()class PROJECTMS_API AMS_AmbientShelfStorage : public AMS_ShelfStorage
{
	GENERATED_BODY()
	
public:
	AMS_AmbientShelfStorage(const FObjectInitializer& aObjectInitializer);

	virtual void PostInitializeComponents() override;
	
protected:
	virtual void BeginPlay() override;
};
