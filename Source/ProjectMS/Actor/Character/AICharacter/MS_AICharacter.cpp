#include "Actor/Character/AICharacter/MS_AICharacter.h"

#include "Components/CapsuleComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "AI/AIController/MS_AIController.h"

AMS_AICharacter::AMS_AICharacter()
{
	AIControllerClass = AMS_AIController::StaticClass();

	bUseControllerRotationPitch = true;
	bUseControllerRotationRoll = true;
	bUseControllerRotationYaw = true;

	CollisionCapsuleComponent = GetCapsuleComponent();
	CollisionCapsuleComponent->SetupAttachment(SceneComponent);
	CollisionCapsuleComponent->SetCapsuleRadius(20.0f);
	CollisionCapsuleComponent->SetCapsuleHalfHeight(50.0f);

	SkeletalMeshComponent = GetMesh();
	SkeletalMeshComponent->SetupAttachment(CollisionCapsuleComponent);

#if WITH_EDITOR
	GetArrowComponent()->SetupAttachment(CollisionCapsuleComponent);
#endif

	CharacterMovementComponent = Cast<UCharacterMovementComponent>(GetMovementComponent());
	CharacterMovementComponent->MaxAcceleration = 512.0f;
	CharacterMovementComponent->MaxWalkSpeed = 75.0f;
	CharacterMovementComponent->MaxWalkSpeedCrouched = 150.0f;
	CharacterMovementComponent->RotationRate = FRotator(0.0f, 630.0f, 0.0f);
}

void AMS_AICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	CharacterMovementComponent->SetAvoidanceEnabled(false);
}

void AMS_AICharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AMS_AICharacter::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
}
