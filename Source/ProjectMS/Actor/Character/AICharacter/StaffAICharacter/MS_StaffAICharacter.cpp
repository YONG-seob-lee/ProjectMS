#include "Actor/Character/AICharacter/StaffAICharacter/MS_StaffAICharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

#include "AI/AIController/StaffAIController/MS_StaffAIController.h"
#include "AI/AIController/StaffAIController/AnimInstance/MS_StaffAIAnimInstance.h"

AMS_StaffAICharacter::AMS_StaffAICharacter()
{
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

	CollisionCapsuleComponent->SetCollisionProfileName(TEXT("CustomerCollisionPreset"));

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

void AMS_StaffAICharacter::SetWorkAnimationFlag(const bool& aWorkFlag)
{
	Cast<UMS_StaffAIAnimInstance>(SkeletalMeshComponent->GetAnimInstance())->SetOwnerWorkFlag(aWorkFlag);
}
