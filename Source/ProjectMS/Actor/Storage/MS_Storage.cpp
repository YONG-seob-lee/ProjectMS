#include "Actor/Storage/MS_Storage.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

#include "Component/Storage/MS_StorageAssemblyAreaComponent.h"
#include "Component/Storage/MS_StorageBayComponent.h"
#include "Component/Storage/MS_StorageSlotComponent.h"

AMS_Storage::AMS_Storage()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);

	StorageStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StorageStaticMeshComponent"));
	StorageStaticMeshComponent->SetupAttachment(GetRootComponent());

	StorageAssemblyAreaComponent = CreateDefaultSubobject<UMS_StorageAssemblyAreaComponent>(TEXT("StorageAssemblyAreaComponent"));
	StorageAssemblyAreaComponent->SetupAttachment(GetRootComponent());
	StorageAssemblyAreaComponent->SetRelativeLocation(FVector(-75.0f, 0.0f, 0.0f));

	int BayComponentIndex = INT_MIN;
	BayComponentIndex = BayComponentArray.Add(CreateDefaultSubobject<UMS_StorageBayComponent>(TEXT("NO1StorageBayComponent")));
	BayComponentArray[BayComponentIndex]->SetupAttachment(GetRootComponent());
	BayComponentArray[BayComponentIndex]->SetRelativeLocation(FVector(-100.0f, 0.0f, 0.0f));
	BayComponentArray[BayComponentIndex]->BayOrder = BayComponentIndex;

	int SlotComponentIndex = INT_MIN;
	SlotComponentIndex = SlotComponentArray.Add(CreateDefaultSubobject<UMS_StorageSlotComponent>(TEXT("NO1StorageSlotComponent")));
	SlotComponentArray[SlotComponentIndex]->SetupAttachment(GetRootComponent());
	SlotComponentArray[SlotComponentIndex]->SlotOrder = SlotComponentIndex;
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