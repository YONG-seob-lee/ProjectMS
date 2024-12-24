#include "Actor/Storage/MS_Storage.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

#include "Component/Storage/MS_StorageAssemblyAreaComponent.h"
#include "Component/Storage/MS_StorageBayComponent.h"


AMS_Storage::AMS_Storage()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);

	StorageStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StorageStaticMeshComponent"));
	StorageStaticMeshComponent->SetupAttachment(SceneComponent);

	StorageBayComponent = CreateDefaultSubobject<UMS_StorageBayComponent>(TEXT("StorageBayComponent"));
	StorageBayComponent->SetupAttachment(SceneComponent);
	StorageBayComponent->SetRelativeLocation(FVector(-100.0f, 0.0f, 0.0f));

	StorageAssemblyAreaComponent = CreateDefaultSubobject<UMS_StorageAssemblyAreaComponent>(TEXT("StorageAssemblyAreaComponent"));
	StorageAssemblyAreaComponent->SetupAttachment(SceneComponent);
	StorageAssemblyAreaComponent->SetRelativeLocation(FVector(-75.0f, 0.0f, 0.0f));
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