#include "Actor/Prop/Furniture/Storage/Display/FrozenDisplay/MS_FrozenDisplayStorage.h"

AMS_FrozenDisplayStorage::AMS_FrozenDisplayStorage(const FObjectInitializer& aObjectInitializer)
	: Super(aObjectInitializer)
{
	if (MeshComponents.IsValidIndex(0))
	{
		if (UStaticMeshComponent* StaticMeshComponent = Cast<UStaticMeshComponent>(MeshComponents[0]))
		{
			const ConstructorHelpers::FObjectFinder<UStaticMesh> AmbientDisplayStaticMeshFinder(TEXT("/Game/3D/StaticMesh/SM_FUR_FG_A"));
			MS_CHECK(AmbientDisplayStaticMeshFinder.Object);
		
			StaticMeshComponent->SetStaticMesh(AmbientDisplayStaticMeshFinder.Object);
		}
	}
}

void AMS_FrozenDisplayStorage::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AMS_FrozenDisplayStorage::BeginPlay()
{
	Super::BeginPlay();
}
