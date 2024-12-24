#include "Component/Storage/MS_StorageSlotComponent.h"

#include "Actor/Storage/MS_Storage.h"

#include "Components/LineBatchComponent.h"
#include "BehaviorTree/BlackboardComponent.h"


UMS_StorageSlotComponent::UMS_StorageSlotComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bWantsInitializeComponent = true;

	SetCollisionProfileName(TEXT("NoCollision"));
	SlotSize.X = SlotSize.Y = SlotSize.Z = 50.0f;
}

#if WITH_EDITOR
void UMS_StorageSlotComponent::OnComponentCreated()
{
	Super::OnComponentCreated();

	DrawSlotOutline();
}

void UMS_StorageSlotComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	Super::OnComponentDestroyed(bDestroyingHierarchy);

	EraseSlotOutline();
}

void UMS_StorageSlotComponent::OnRegister()
{
	Super::OnRegister();

	RedrawSlotOutline();
}

void UMS_StorageSlotComponent::InitializeComponent()
{
	Super::InitializeComponent();

	if (GetOwner() == nullptr && Cast<AMS_Storage>(GetOwner()) != nullptr)
	{
		checkNoEntry();
	}

	OwnerInst = Cast<AMS_Storage>(GetOwner());
}

void UMS_StorageSlotComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	FName ChangedMemberPropertyName = (PropertyChangedEvent.MemberProperty != nullptr ? PropertyChangedEvent.MemberProperty->GetFName() : NAME_None);
	if (ChangedMemberPropertyName == FName("RelativeLocation") || ChangedMemberPropertyName == FName("RelativeRotation") || ChangedMemberPropertyName == FName("SlotOutlineColor") || ChangedMemberPropertyName == FName("SlotOutlineThickness"))
	{
		RedrawSlotOutline();
	}
	else if (ChangedMemberPropertyName == FName("SlotSize"))
	{
		RedrawSlotOutline();
	}
}

void UMS_StorageSlotComponent::PostEditComponentMove(bool bFinished)
{
	Super::PostEditComponentMove(bFinished);

	RedrawSlotOutline();
}

void UMS_StorageSlotComponent::PostEditUndo()
{
	Super::PostEditUndo();

	RedrawSlotOutline();
}

void UMS_StorageSlotComponent::DrawSlotOutline()
{
	if (GetWorld() != nullptr)
	{
		GetWorld()->PersistentLineBatcher->DrawBox(GetComponentLocation(), SlotSize / 2.0f, GetComponentRotation().Quaternion(), SlotOutlineColor, -1.0f, SDPG_World, SlotOutlineThickness, GetUniqueID());
	}
}

void UMS_StorageSlotComponent::RedrawSlotOutline()
{
	if (GetWorld() != nullptr)
	{
		GetWorld()->PersistentLineBatcher->ClearBatch(GetUniqueID());
		GetWorld()->PersistentLineBatcher->DrawBox(GetComponentLocation(), SlotSize / 2.0f, GetComponentRotation().Quaternion(), SlotOutlineColor, -1.0f, SDPG_World, SlotOutlineThickness, GetUniqueID());
	}
}

void UMS_StorageSlotComponent::EraseSlotOutline()
{
	if (GetWorld() != nullptr)
	{
		GetWorld()->PersistentLineBatcher->ClearBatch(GetUniqueID());
	}
}
#endif

void UMS_StorageSlotComponent::ReserveWorker(AMS_StaffAICharacter* aTarget)
{
	ReservationFlag = true;
	ReservationWorker = aTarget;
}

void UMS_StorageSlotComponent::UnreserveWorker()
{
	ReservationFlag = false;
	ReservationWorker = nullptr;
}

bool UMS_StorageSlotComponent::LoadStuff(FName aStuffRowName, int aStockQuantity)
{
	return true;
}

void UMS_StorageSlotComponent::UnloadStuff()
{
}