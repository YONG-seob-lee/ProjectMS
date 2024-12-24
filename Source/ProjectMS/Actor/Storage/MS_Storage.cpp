#include "Actor/Storage/MS_Storage.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

#include "Component/Prop/MS_StorageOperationSpotComponent.h"

AMS_Storage::AMS_Storage()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	StorageStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StorageStaticMeshComponent"));
	OperationSpotComponent = CreateDefaultSubobject<UMS_StorageOperationSpotComponent>(TEXT("OperationSpotComponent"));

	SetRootComponent(SceneComponent);
	StorageStaticMeshComponent->SetupAttachment(SceneComponent);
	OperationSpotComponent->SetupAttachment(SceneComponent);

	OperationSpotComponent->SetRelativeLocation(FVector(-100.0f, 0.0f, 0.0f));
}

void AMS_Storage::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AMS_Storage::BeginPlay()
{
	Super::BeginPlay();
}

void AMS_Storage::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
}