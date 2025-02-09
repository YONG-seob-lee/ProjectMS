#pragma once

#include "CoreMinimal.h"
#include "Prop/Furniture/MS_Furniture.h"
#include "MS_Storage.generated.h"


UCLASS()
class PROJECTMS_API AMS_Storage : public AMS_Furniture
{
	GENERATED_BODY()
	
public:
	AMS_Storage(const FObjectInitializer& aObjectInitializer);

	virtual void PostInitializeComponents() override;

protected:
	virtual void BeginPlay() override;
};