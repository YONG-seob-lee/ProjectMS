#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MS_AIController.generated.h"


UCLASS()
class PROJECTMS_API AMS_AIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AMS_AIController();

	virtual void PostInitializeComponents() override;
	virtual void OnPossess(APawn* aInPawn) override;
	virtual void OnUnPossess() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type aEndPlayReason) override;
};
