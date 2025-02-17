#include "Actor/Character/AICharacter/StaffAICharacter/MS_StaffAICharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "AI/AIController/StaffAIController/MS_StaffAIController.h"
#include "Component/Actor/Character/MS_MovingBoxComponent.h"
#include "Components/CapsuleComponent.h"


AMS_StaffAICharacter::AMS_StaffAICharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	AIControllerClass = AMS_StaffAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	if (GetCapsuleComponent())
	{
		GetCapsuleComponent()->SetCollisionProfileName(TEXT("ClickableShape"));
	}

	if (GetMesh())
	{
		GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	}
	
	UCharacterMovementComponent* CharacterMovementComponent = Cast<UCharacterMovementComponent>(GetMovementComponent());
	if (CharacterMovementComponent)
	{
		CharacterMovementComponent->GravityScale = 0.f;
	}
}

void AMS_StaffAICharacter::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	// Component
	GetComponents<UMS_MovingBoxComponent>(MovingBoxComponents);

	// Component
	TArray<UPrimitiveComponent*> PrimitiveComponents;
	GetComponents<UPrimitiveComponent>(PrimitiveComponents);

	// Physics off
	for (UPrimitiveComponent* PrimitiveComponent : PrimitiveComponents)
	{
		PrimitiveComponent->SetSimulatePhysics(false);
		PrimitiveComponent->SetEnableGravity(false);
	}

	// Z 위치 보정
	if (GetCapsuleComponent())
    {
		FVector Location = GetActorLocation();
    	float LocationZ = GetCapsuleComponent()->GetScaledCapsuleHalfHeight();

		SetActorLocation(FVector(Location.X, Location.Y, LocationZ));
    }
}

void AMS_StaffAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// Physics off
	TArray<UPrimitiveComponent*> PrimitiveComponents;
	GetComponents<UPrimitiveComponent>(PrimitiveComponents);
	
	for (UPrimitiveComponent* PrimitiveComponent : PrimitiveComponents)
	{
		PrimitiveComponent->SetSimulatePhysics(false);
		PrimitiveComponent->SetEnableGravity(false);
	}

	// Z 위치 보정
	if (GetCapsuleComponent())
	{
		FVector Location = GetActorLocation();
		float LocationZ = GetCapsuleComponent()->GetScaledCapsuleHalfHeight();

		SetActorLocation(FVector(Location.X, Location.Y, LocationZ));
	}
}

void AMS_StaffAICharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AMS_StaffAICharacter::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);

	FVector DirectionVector = UMS_MathUtility::ConvertDirectionToVector(Direction);
	FRotator DirectionRotator = UMS_MathUtility::ConvertDirectionToRotator(Direction);
	SetActorLocation(GetActorLocation() + DirectionVector * DuckVelocity * aDeltaTime);
	SetActorRotation(DirectionRotator);
}