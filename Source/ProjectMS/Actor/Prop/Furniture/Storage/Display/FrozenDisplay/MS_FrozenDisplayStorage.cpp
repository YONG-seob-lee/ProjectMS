#include "Actor/Prop/Furniture/Storage/Display/FrozenDisplay/MS_FrozenDisplayStorage.h"

AMS_FrozenDisplayStorage::AMS_FrozenDisplayStorage()
{
	const ConstructorHelpers::FObjectFinder<UStaticMesh> AmbientDisplayStaticMeshFinder(TEXT("/Game/3D/StaticMesh/SM_FUR_FG_A"));
	MS_CHECK(AmbientDisplayStaticMeshFinder.Object);

	StorageStaticMeshComponent->SetStaticMesh(AmbientDisplayStaticMeshFinder.Object);
}

void AMS_FrozenDisplayStorage::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AMS_FrozenDisplayStorage::BeginPlay()
{
	Super::BeginPlay();
}

void AMS_FrozenDisplayStorage::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
}
