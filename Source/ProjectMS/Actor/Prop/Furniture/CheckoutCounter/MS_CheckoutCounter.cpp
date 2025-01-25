#include "Actor/Prop/Furniture/CheckoutCounter/MS_CheckoutCounter.h"

#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

AMS_CheckoutCounter::AMS_CheckoutCounter(const FObjectInitializer& aObjectInitializer)
	: Super(aObjectInitializer)
{
	if (MeshComponents.IsValidIndex(0))
	{
		if (UStaticMeshComponent* StaticMeshComponent = Cast<UStaticMeshComponent>(MeshComponents[0]))
		{
			const ConstructorHelpers::FObjectFinder<UStaticMesh> AmbientDisplayStaticMeshFinder(TEXT("/Game/3D/StaticMesh/SM_FUR_COT_A"));
			MS_CHECK(AmbientDisplayStaticMeshFinder.Object);
		
			StaticMeshComponent->SetStaticMesh(AmbientDisplayStaticMeshFinder.Object);
		}
	}
	
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
