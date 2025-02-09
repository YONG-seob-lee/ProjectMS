#pragma once

#include "CoreMinimal.h"
#include "Actor/MS_Actor.h"
#include "MS_CustomerSuperviseActor.generated.h"


UCLASS()
class PROJECTMS_API AMS_CustomerSuperviseActor : public AMS_Actor
{
	GENERATED_BODY()
	
public:
	AMS_CustomerSuperviseActor(const FObjectInitializer& aObjectInitializer);

protected:
	virtual void BeginPlay() override;
};
