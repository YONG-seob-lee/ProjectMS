#include "Actor/Character/AICharacter/CustomerAICharacter/MS_CustomerAICharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

#include "AI/AIController/StaffAIController/MS_StaffAIController.h"
#include "AI/AIController/StaffAIController/AnimInstance/MS_StaffAIAnimInstance.h"

AMS_CustomerAICharacter::AMS_CustomerAICharacter()
{
	// Temp Staff AI Animations
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMeshFinder(TEXT("/Game/3D/Character/Ch_Duck"));
	static ConstructorHelpers::FClassFinder<UMS_StaffAIAnimInstance> AnimInstanceFinder(TEXT("/Game/AI/AIController/StaffAIController/AnimInstance/BP_StaffAIAnimInstance"));

	MS_CHECK(SkeletalMeshFinder.Object);
	MS_CHECK(AnimInstanceFinder.Class);

	AIControllerClass = AMS_StaffAIController::StaticClass();
	SkeletalMeshComponent->SetRelativeLocation(FVector(0.0f, 0.0f, -50.0f));
	SkeletalMeshComponent->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	SkeletalMeshComponent->SetSkeletalMesh(SkeletalMeshFinder.Object);
	SkeletalMeshComponent->SetAnimInstanceClass(AnimInstanceFinder.Class);

	bUseControllerRotationPitch = true;
	bUseControllerRotationRoll = true;
	bUseControllerRotationYaw = true;
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
