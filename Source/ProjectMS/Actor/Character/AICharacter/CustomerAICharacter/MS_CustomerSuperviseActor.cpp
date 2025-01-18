#include "Actor/Character/AICharacter/CustomerAICharacter/MS_CustomerSuperviseActor.h"

#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"

AMS_CustomerSuperviseActor::AMS_CustomerSuperviseActor()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(RootComponent);
	BoxComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 150.0f));
	BoxComponent->SetBoxExtent(FVector(150.0f, 150.0f, 150.0f));
}

void AMS_CustomerSuperviseActor::BeginPlay()
{
	Super::BeginPlay();
}

void AMS_CustomerSuperviseActor::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
}

void AMS_CustomerSuperviseActor::SpawnCustomerCharacter(const FMS_CustomerSpawnParameters& aSpawnParams)
{
    FActorSpawnParameters SpawnParams;
    SpawnParams.bNoFail = true;
    SpawnParams.Name = MakeUniqueObjectName(GetWorld(), AMS_CustomerAICharacter::StaticClass(), aSpawnParams.CustomerName);
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    auto CustomerCharacter = GetWorld()->SpawnActor<AMS_CustomerAICharacter>(AMS_CustomerAICharacter::StaticClass(), GetActorLocation(), GetActorRotation(), SpawnParams);

    if (!CustomerCharacter)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to spawn CustomerCharacter."));
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("CustomerCharacter spawned successfully: %s"), *CustomerCharacter->GetName());
}


void AMS_CustomerSuperviseActor::DestroyCustomerCharacter(AMS_CustomerAICharacter* aCharacter)
{
}
