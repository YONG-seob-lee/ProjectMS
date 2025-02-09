#include "AI/AIController/MS_AIController.h"


AMS_AIController::AMS_AIController()
{
}

void AMS_AIController::PostInitializeComponents()
{
    Super::PostInitializeComponents();
}

void AMS_AIController::OnPossess(APawn* aInPawn)
{
	Super::OnPossess(aInPawn);
}

void AMS_AIController::OnUnPossess()
{
	Super::OnUnPossess();
}

void AMS_AIController::BeginPlay()
{
	Super::BeginPlay();
}

void AMS_AIController::EndPlay(const EEndPlayReason::Type aEndPlayReason)
{
	Super::EndPlay(aEndPlayReason);
}