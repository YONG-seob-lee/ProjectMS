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
	CollisionCapsuleComponent->SetCollisionProfileName(TEXT("StaffCollisionPreset"));

	SkeletalMeshComponent = GetMesh();
	SkeletalMeshComponent->SetupAttachment(CollisionCapsuleComponent);
	SkeletalMeshComponent->SetCollisionProfileName(TEXT("NoCollision"));
	SkeletalMeshComponent->SetRenderCustomDepth(true);

#if WITH_EDITOR
	GetArrowComponent()->SetupAttachment(CollisionCapsuleComponent);
#endif

	CharacterMovementComponent = Cast<UCharacterMovementComponent>(GetMovementComponent());
	CharacterMovementComponent->MaxAcceleration = 512.0f;
	CharacterMovementComponent->MaxWalkSpeed = /*75.0f*/300.0f;
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

	LoadResourceDelegate.BindUFunction(this, TEXT("OnLoadResource"));
}

void AMS_AICharacter::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
}

void AMS_AICharacter::OnLoadResource(FString aName, UObject* aObject)
{
	UE_LOG(LogTemp, Warning, TEXT("Name: %s"), *aName);
	if (aObject != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemName: %s"), *aObject->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Object nullptr"));
	}
}
