#include "Actor/Character/AICharacter/StaffAICharacter/MS_StaffAICharacter.h"

#include "AI/AIController/StaffAIController/MS_StaffAIController.h"


AMS_StaffAICharacter::AMS_StaffAICharacter()
{
	AIControllerClass = AMS_StaffAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AMS_StaffAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AMS_StaffAICharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AMS_StaffAICharacter::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
}