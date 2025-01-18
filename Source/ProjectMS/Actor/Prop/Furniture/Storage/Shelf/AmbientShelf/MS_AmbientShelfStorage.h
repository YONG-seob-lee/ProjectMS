#pragma once

#include "CoreMinimal.h"
#include "Actor/Prop/Furniture/Storage/Shelf/MS_ShelfStorage.h"
#include "MS_AmbientShelfStorage.generated.h"

UCLASS()class PROJECTMS_API AMS_AmbientShelfStorage : public AMS_ShelfStorage
{
	GENERATED_BODY()
	
public:
	AMS_AmbientShelfStorage();

	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float aDeltaTime) override;

};
