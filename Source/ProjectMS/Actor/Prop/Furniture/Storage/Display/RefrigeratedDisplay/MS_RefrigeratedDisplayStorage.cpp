#include "Actor/Prop/Furniture/Storage/Display/RefrigeratedDisplay/MS_RefrigeratedDisplayStorage.h"

AMS_RefrigeratedDisplayStorage::AMS_RefrigeratedDisplayStorage(const FObjectInitializer& aObjectInitializer)
	: Super(aObjectInitializer)
{
	if (MeshComponents.IsValidIndex(0))
	{
		if (UStaticMeshComponent* StaticMeshComponent = Cast<UStaticMeshComponent>(MeshComponents[0]))
		{
			const ConstructorHelpers::FObjectFinder<UStaticMesh> AmbientDisplayStaticMeshFinder(TEXT("/Game/3D/StaticMesh/SM_FUR_FZ_A"));
			MS_CHECK(AmbientDisplayStaticMeshFinder.Object);
		
			StaticMeshComponent->SetStaticMesh(AmbientDisplayStaticMeshFinder.Object);
		}
	}
}

void AMS_RefrigeratedDisplayStorage::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AMS_RefrigeratedDisplayStorage::BeginPlay()
{
	Super::BeginPlay();
}
