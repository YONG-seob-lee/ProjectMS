#include "Actor/Storage/CheckoutCounter/MS_CheckoutCounterStorage.h"

AMS_CheckoutCounterStorage::AMS_CheckoutCounterStorage()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CheckoutCounterStaticMeshFinder(TEXT("/Game/3D/StaticMesh/SM_FUR_COT_A"));
	MS_CHECK(CheckoutCounterStaticMeshFinder.Object);

	StorageStaticMeshComponent->SetStaticMesh(CheckoutCounterStaticMeshFinder.Object);

	SlotComponentArray[SlotComponentIndexSize]->Rename(TEXT("CheckoutCounterSlotComponent"));
}

void AMS_CheckoutCounterStorage::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AMS_CheckoutCounterStorage::BeginPlay()
{
	Super::BeginPlay();
}

void AMS_CheckoutCounterStorage::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
}
