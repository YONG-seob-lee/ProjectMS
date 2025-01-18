#pragma once

#include "CoreMinimal.h"
#include "Actor/Prop/Furniture/Storage/MS_Storage.h"
#include "MS_PalletStorage.generated.h"

UCLASS() class PROJECTMS_API AMS_PalletStorage : public AMS_Storage
{
	GENERATED_BODY()
	
public:
	AMS_PalletStorage();

	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float aDeltaTime) override;
};
