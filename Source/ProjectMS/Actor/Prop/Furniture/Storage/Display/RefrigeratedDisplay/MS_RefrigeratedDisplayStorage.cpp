#include "Actor/Prop/Furniture/Storage/Display/RefrigeratedDisplay/MS_RefrigeratedDisplayStorage.h"

AMS_RefrigeratedDisplayStorage::AMS_RefrigeratedDisplayStorage()
{
	const ConstructorHelpers::FObjectFinder<UStaticMesh> AmbientDisplayStaticMeshFinder(TEXT("/Game/3D/StaticMesh/SM_FUR_FZ_A"));
	MS_CHECK(AmbientDisplayStaticMeshFinder.Object);

	StorageStaticMeshComponent->SetStaticMesh(AmbientDisplayStaticMeshFinder.Object);
}

void AMS_RefrigeratedDisplayStorage::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AMS_RefrigeratedDisplayStorage::BeginPlay()
{
	Super::BeginPlay();
}

void AMS_RefrigeratedDisplayStorage::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
}
