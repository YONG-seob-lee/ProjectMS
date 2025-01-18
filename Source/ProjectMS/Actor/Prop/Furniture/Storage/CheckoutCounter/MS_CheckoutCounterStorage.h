#pragma once

#include "CoreMinimal.h"
#include "Actor/Prop/Furniture/Storage/MS_Storage.h"
#include "MS_CheckoutCounterStorage.generated.h"

UCLASS() class PROJECTMS_API AMS_CheckoutCounterStorage : public AMS_Storage
{
	GENERATED_BODY()
	
public:
	AMS_CheckoutCounterStorage();

	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float aDeltaTime) override;
};
