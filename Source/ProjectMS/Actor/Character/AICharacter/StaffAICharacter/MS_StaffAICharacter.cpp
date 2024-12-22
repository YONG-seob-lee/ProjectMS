#include "Actor/Character/AICharacter/StaffAICharacter/MS_StaffAICharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

#include "AI/AIController/StaffAIController/MS_StaffAIController.h"

AMS_StaffAICharacter::AMS_StaffAICharacter()
{
	AIControllerClass = AMS_StaffAIController::StaticClass();

	SkeletalMeshComponent->SetRelativeLocation(FVector(0.0f, 0.0f, -50.0f));

	bUseControllerRotationPitch = true;
	bUseControllerRotationRoll = true;
	bUseControllerRotationYaw = true;
}

void AMS_StaffAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	CharacterMovementComponent->SetAvoidanceEnabled(false);
}

void AMS_StaffAICharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AMS_StaffAICharacter::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
}
