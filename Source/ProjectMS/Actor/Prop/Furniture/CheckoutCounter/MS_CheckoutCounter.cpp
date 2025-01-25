#include "Actor/Prop/Furniture/CheckoutCounter/MS_CheckoutCounter.h"

#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

AMS_CheckoutCounter::AMS_CheckoutCounter(const FObjectInitializer& aObjectInitializer)
	: Super(aObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CheckoutCounterFiner(TEXT("/Game/3D/StaticMesh/SM_FUR_COT_A"));
	MS_CHECK(CheckoutCounterFiner.Object);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StorageStaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(GetRootComponent());
	StaticMeshComponent->SetStaticMesh(CheckoutCounterFiner.Object);
	StaticMeshComponent->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	StaticMeshComponent->SetCollisionProfileName(TEXT("NoCollision"));
	
	CollisionBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBoxComponent"));
	CollisionBoxComponent->SetupAttachment(GetRootComponent());
	CollisionBoxComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f));
	CollisionBoxComponent->SetCollisionProfileName(TEXT("CheckoutCounterCollisionPreset"));
	CollisionBoxComponent->SetBoxExtent(FVector(50.0f, 150.0f, 50.0f));
}

void AMS_CheckoutCounter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AMS_CheckoutCounter::BeginPlay()
{
	Super::BeginPlay();
}
