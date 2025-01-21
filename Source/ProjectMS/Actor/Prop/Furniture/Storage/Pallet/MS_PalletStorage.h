#pragma once

#include "CoreMinimal.h"
#include "Actor/Prop/Furniture/Storage/MS_Storage.h"
#include "MS_PalletStorage.generated.h"

UCLASS() class PROJECTMS_API AMS_PalletStorage : public AMS_Storage
{
	GENERATED_BODY()
	
public:
	AMS_PalletStorage(const FObjectInitializer& aObjectInitializer);

	virtual void PostInitializeComponents() override;
	
protected:
	virtual void BeginPlay() override;
};
