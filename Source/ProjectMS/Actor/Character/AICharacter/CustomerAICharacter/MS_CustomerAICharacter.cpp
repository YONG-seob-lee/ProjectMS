#include "Actor/Character/AICharacter/CustomerAICharacter/MS_CustomerAICharacter.h"

#include "AI/AIController/CustomerAIController/MS_CustomerAIController.h"


AMS_CustomerAICharacter::AMS_CustomerAICharacter()
{
	AIControllerClass = AMS_CustomerAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AMS_CustomerAICharacter::PreInitializeComponents()
{
	Super::PreInitializeComponents();
}

void AMS_CustomerAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AMS_CustomerAICharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AMS_CustomerAICharacter::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
}
