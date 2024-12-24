#include "Actor/Storage/Display/AmbientDisplay/MS_AmbientDisplayStorage.h"

AMS_AmbientDisplayStorage::AMS_AmbientDisplayStorage()
{
	const ConstructorHelpers::FObjectFinder<UStaticMesh> AmbientDisplayStaticMeshFinder(TEXT("/Game/3D/StaticMesh/SM_FUR_RT_A"));
	MS_CHECK(AmbientDisplayStaticMeshFinder.Object);

	StorageStaticMeshComponent->SetStaticMesh(AmbientDisplayStaticMeshFinder.Object);
}

void AMS_AmbientDisplayStorage::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AMS_AmbientDisplayStorage::BeginPlay()
{
	Super::BeginPlay();
}

void AMS_AmbientDisplayStorage::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
}
