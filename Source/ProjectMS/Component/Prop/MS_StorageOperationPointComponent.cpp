#include "Component/Prop/MS_StorageOperationPointComponent.h"

#include "Actor/Prop/Storage/MS_Prop_Storage.h"

UMS_StorageOperationPointComponent::UMS_StorageOperationPointComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UMS_StorageOperationPointComponent::InitializeComponent()
{
	Super::InitializeComponent();

	OwnerStorage = Cast<AMS_Prop_Storage>(GetOwner());
	MS_CHECK(OwnerStorage);
}

void UMS_StorageOperationPointComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UMS_StorageOperationPointComponent::TickComponent(float aDeltaTime, ELevelTick aTickType, FActorComponentTickFunction* aThisTickFunction)
{
	Super::TickComponent(aDeltaTime, aTickType, aThisTickFunction);
}
