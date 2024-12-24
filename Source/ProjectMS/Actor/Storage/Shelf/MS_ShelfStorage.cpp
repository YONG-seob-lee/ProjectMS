#include "Actor/Storage/Shelf/MS_ShelfStorage.h"

AMS_ShlefStorage::AMS_ShlefStorage()
{
	const ConstructorHelpers::FObjectFinder<UStaticMesh> AmbientDisplayStaticMeshFinder(TEXT("/Game/3D/StaticMesh/SM_WH_RACK"));
	MS_CHECK(AmbientDisplayStaticMeshFinder.Object);

	StorageStaticMeshComponent->SetStaticMesh(AmbientDisplayStaticMeshFinder.Object);
}

void AMS_ShlefStorage::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AMS_ShlefStorage::BeginPlay()
{
	Super::BeginPlay();
}

void AMS_ShlefStorage::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
}
