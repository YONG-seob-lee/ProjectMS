#include "Actor/Prop/Furniture/Storage/Shelf/MS_ShelfStorage.h"

#include "Component/Prop/Furniture/MS_StorageSlotComponent.h"

AMS_ShelfStorage::AMS_ShelfStorage(const FObjectInitializer& aObjectInitializer)
	: Super(aObjectInitializer)
{
	if (MeshComponents.IsValidIndex(0))
	{
		if (UStaticMeshComponent* StaticMeshComponent = Cast<UStaticMeshComponent>(MeshComponents[0]))
		{
			const ConstructorHelpers::FObjectFinder<UStaticMesh> AmbientDisplayStaticMeshFinder(TEXT("/Game/3D/StaticMesh/SM_WH_RACK"));
			MS_CHECK(AmbientDisplayStaticMeshFinder.Object);
		
			StaticMeshComponent->SetStaticMesh(AmbientDisplayStaticMeshFinder.Object);
		}
	}
	
	SlotComponentArray[SlotComponentIndexSize]->SetRelativeLocation(FVector(0.0f, -45.0f, 0.0f));

	SlotComponentIndexSize = SlotComponentArray.Add(CreateDefaultSubobject<UMS_StorageSlotComponent>(TEXT("No2StorageSlotComponent")));
	SlotComponentArray[SlotComponentIndexSize]->SetupAttachment(SceneRootComponent);
	SlotComponentArray[SlotComponentIndexSize]->SlotOrder = SlotComponentIndexSize;
	SlotComponentArray[SlotComponentIndexSize]->SetRelativeLocation(FVector(0.0f, 45.0f, 0.0f));

	SlotComponentIndexSize = SlotComponentArray.Add(CreateDefaultSubobject<UMS_StorageSlotComponent>(TEXT("No3StorageSlotComponent")));
	SlotComponentArray[SlotComponentIndexSize]->SetupAttachment(SceneRootComponent);
	SlotComponentArray[SlotComponentIndexSize]->SlotOrder = SlotComponentIndexSize;
	SlotComponentArray[SlotComponentIndexSize]->SetRelativeLocation(FVector(0.0f, -45.0f, 100.0f));

	SlotComponentIndexSize = SlotComponentArray.Add(CreateDefaultSubobject<UMS_StorageSlotComponent>(TEXT("No4StorageSlotComponent")));
	SlotComponentArray[SlotComponentIndexSize]->SetupAttachment(SceneRootComponent);
	SlotComponentArray[SlotComponentIndexSize]->SlotOrder = SlotComponentIndexSize;
	SlotComponentArray[SlotComponentIndexSize]->SetRelativeLocation(FVector(0.0f, 45.0f, 100.0f));
}

void AMS_ShelfStorage::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AMS_ShelfStorage::BeginPlay()
{
	Super::BeginPlay();
}