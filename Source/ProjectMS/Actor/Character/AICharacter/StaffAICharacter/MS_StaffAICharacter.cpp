#include "Actor/Character/AICharacter/StaffAICharacter/MS_StaffAICharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

#include "AI/AIController/StaffAIController/MS_StaffAIController.h"

AMS_StaffAICharacter::AMS_StaffAICharacter()
{
	AIControllerClass = AMS_StaffAIController::StaticClass();
	SkeletalMeshComponent->SetRelativeLocation(FVector(0.0f, 0.0f, -50.0f));

	bUseControllerRotationPitch = true;
	bUseControllerRotationRoll = true;
	bUseControllerRotationYaw = true;

	CollisionCapsuleComponent->SetCollisionProfileName(TEXT("StaffCollisionPreset"));

	StockStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StockStaticMeshComponent"));
	StockStaticMeshComponent->SetupAttachment(SkeletalMeshComponent);

	StockStaticMeshComponent->SetCollisionProfileName(TEXT("NoCollision"));
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

UClass* AMS_StaffAICharacter::GetLoadingStorageType()
{
	return nullptr;
}

UClass* AMS_StaffAICharacter::GetUnloadingStorageType()
{
	return nullptr;
}

void AMS_StaffAICharacter::AttachStockStaticMesh(UStaticMesh* aStockStaticMesh)
{
	StockStaticMeshComponent->SetStaticMesh(aStockStaticMesh);
	UE_LOG(LogTemp, Warning, TEXT("Hello World %s"), *aStockStaticMesh->GetName());
}

void AMS_StaffAICharacter::DeattachStockStaticMesh()
{
	StockStaticMeshComponent->SetStaticMesh(nullptr);
}
