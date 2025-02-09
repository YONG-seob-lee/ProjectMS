#pragma once

#include "CoreMinimal.h"
#include "Actor/Prop/Furniture/MS_Furniture.h"
#include "MS_Counter.generated.h"

UCLASS()
class PROJECTMS_API AMS_Counter : public AMS_Furniture
{
	GENERATED_BODY()
	
public:
	AMS_Counter(const FObjectInitializer& aObjectInitializer);

	virtual void PostInitializeComponents() override;
	
protected:
	virtual void BeginPlay() override;
};
