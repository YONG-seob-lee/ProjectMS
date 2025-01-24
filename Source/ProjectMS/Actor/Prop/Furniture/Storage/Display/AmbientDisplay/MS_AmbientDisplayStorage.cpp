#include "Actor/Prop/Furniture/Storage/Display/AmbientDisplay/MS_AmbientDisplayStorage.h"

#include "Component/Prop/Furniture/MS_StorageSlotComponent.h"

AMS_AmbientDisplayStorage::AMS_AmbientDisplayStorage(const FObjectInitializer& aObjectInitializer)
	: Super(aObjectInitializer)
{
	if (MeshComponents.IsValidIndex(0))
	{
		if (UStaticMeshComponent* StaticMeshComponent = Cast<UStaticMeshComponent>(MeshComponents[0]))
		{
			const ConstructorHelpers::FObjectFinder<UStaticMesh> AmbientDisplayStaticMeshFinder(TEXT("/Game/3D/StaticMesh/SM_FUR_RT_A"));
			MS_CHECK(AmbientDisplayStaticMeshFinder.Object);
		
			StaticMeshComponent->SetStaticMesh(AmbientDisplayStaticMeshFinder.Object);
		}
	}
	
	SlotComponentArray[0]->SlotSize = FVector(90.0f, 90.0f, 10.0f);
	SlotComponentArray[0]->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f));
	SlotComponentArray[0]->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));

	SlotComponentArray[1]->SlotSize = FVector(90.0f, 90.0f, 10.0f);
	SlotComponentArray[1]->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
	SlotComponentArray[1]->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));

	SlotComponentArray[2]->SlotSize = FVector(90.0f, 90.0f, 10.0f);
	SlotComponentArray[2]->SetRelativeLocation(FVector(0.0f, 0.0f, 150.0f));
	SlotComponentArray[2]->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));

}

void AMS_AmbientDisplayStorage::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AMS_AmbientDisplayStorage::BeginPlay()
{
	Super::BeginPlay();
}
