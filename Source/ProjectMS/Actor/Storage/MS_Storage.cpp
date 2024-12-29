#include "Actor/Storage/MS_Storage.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

AMS_Storage::AMS_Storage()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);

	StorageStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StorageStaticMeshComponent"));
	StorageStaticMeshComponent->SetupAttachment(GetRootComponent());

	StorageAssemblyAreaComponent = CreateDefaultSubobject<UMS_StorageAssemblyAreaComponent>(TEXT("StorageAssemblyAreaComponent"));
	StorageAssemblyAreaComponent->SetupAttachment(GetRootComponent());
	StorageAssemblyAreaComponent->SetRelativeLocation(FVector(-75.0f, 0.0f, 0.0f));

	BayComponentIndexSize = BayComponentArray.Add(CreateDefaultSubobject<UMS_StorageBayComponent>(TEXT("No1StorageBayComponent")));
	BayComponentArray[BayComponentIndexSize]->SetupAttachment(GetRootComponent());
	BayComponentArray[BayComponentIndexSize]->SetRelativeLocation(FVector(-100.0f, 0.0f, 0.0f));
	BayComponentArray[BayComponentIndexSize]->BayOrder = BayComponentIndexSize;

	SlotComponentIndexSize = SlotComponentArray.Add(CreateDefaultSubobject<UMS_StorageSlotComponent>(TEXT("No1StorageSlotComponent")));
	SlotComponentArray[SlotComponentIndexSize]->SetupAttachment(GetRootComponent());
	SlotComponentArray[SlotComponentIndexSize]->SlotOrder = SlotComponentIndexSize;

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