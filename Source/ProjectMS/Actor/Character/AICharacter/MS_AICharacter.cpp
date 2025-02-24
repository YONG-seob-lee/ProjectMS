#include "Actor/Character/AICharacter/MS_AICharacter.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "AI/AIController/MS_AIController.h"
#include "Animation/MS_AIAnimInstance.h"

AMS_AICharacter::AMS_AICharacter()
{
	AIControllerClass = AMS_AIController::StaticClass();

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	
	UCapsuleComponent* CollisionCapsuleComponent = GetCapsuleComponent();
	if (CollisionCapsuleComponent)
	{
		CollisionCapsuleComponent->SetCapsuleRadius(20.0f);
		CollisionCapsuleComponent->SetCapsuleHalfHeight(50.0f);
	}

	USkeletalMeshComponent* SkeletalMeshComponent = GetMesh();
	if (SkeletalMeshComponent)
	{
		SkeletalMeshComponent->SetCollisionProfileName(TEXT("NoCollision"));
		SkeletalMeshComponent->SetRenderCustomDepth(true);
	}

	UCharacterMovementComponent* CharacterMovementComponent = Cast<UCharacterMovementComponent>(GetMovementComponent());
	if (CharacterMovementComponent)
	{
		CharacterMovementComponent->MaxAcceleration = 512.0f;
		CharacterMovementComponent->MaxWalkSpeed = 300.0f;
		CharacterMovementComponent->MaxWalkSpeedCrouched = 150.0f;
		CharacterMovementComponent->RotationRate = FRotator(0.0f, 630.0f, 0.0f);
	}
}

void AMS_AICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AMS_AICharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AMS_AICharacter::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
}

TObjectPtr<UMS_AIAnimInstance> AMS_AICharacter::GetAIAnimInstance() const
{
	const USkeletalMeshComponent* SkeletalMeshComponent = GetMesh();
	if(SkeletalMeshComponent)
	{
		return Cast<UMS_AIAnimInstance>(SkeletalMeshComponent->GetAnimInstance());
	}
	
	return nullptr;
}
