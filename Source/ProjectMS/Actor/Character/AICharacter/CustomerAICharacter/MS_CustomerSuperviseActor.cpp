#include "Actor/Character/AICharacter/CustomerAICharacter/MS_CustomerSuperviseActor.h"

#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"

#include "AI/AIController/CustomerAIController/MS_CustomerAIController.h"

AMS_CustomerSuperviseActor::AMS_CustomerSuperviseActor(const FObjectInitializer& aObjectInitializer)
	: Super(aObjectInitializer)
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

void AMS_CustomerSuperviseActor::SpawnCustomerCharacter(const FMS_CustomerSpawnParameters& aSpawnParams)
{
    FActorSpawnParameters SpawnParams;
    SpawnParams.bNoFail = true;
    SpawnParams.Name = MakeUniqueObjectName(GetWorld(), AMS_CustomerAICharacter::StaticClass(), aSpawnParams.CustomerName);
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AMS_CustomerAICharacter* CustomerCharacter = GetWorld()->SpawnActor<AMS_CustomerAICharacter>(AMS_CustomerAICharacter::StaticClass(), GetActorLocation(), GetActorRotation(), SpawnParams);
	AMS_CustomerAIController* TargetAIController = Cast<AMS_CustomerAIController>(CustomerCharacter->GetController());

	CustomerCharacter->CustomerName = aSpawnParams.CustomerName;
	CustomerCharacter->Age = aSpawnParams.Age;
	CustomerCharacter->Gender = aSpawnParams.Gender;
	CustomerCharacter->WishlistArray = aSpawnParams.WishlistArray;

}

void AMS_CustomerSuperviseActor::DestroyCustomerCharacter(AMS_CustomerAICharacter* aCharacter)
{
}
