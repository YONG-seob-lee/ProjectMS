#include "Component/Storage/MS_StorageAssemblyAreaComponent.h"

#include "Components/CapsuleComponent.h"
#include "Components/LineBatchComponent.h"

#include "Actor/Prop/Furniture/Storage/MS_Storage.h"
#include "Actor/Character/AICharacter/StaffAICharacter/MS_StaffAICharacter.h"
#include "Component/Storage/MS_StorageBayComponent.h"

UMS_StorageAssemblyAreaComponent::UMS_StorageAssemblyAreaComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bWantsInitializeComponent = true;

	SetCollisionProfileName(TEXT("NoCollision"));
	AssemblyAreaSize.X = 100.0f;
	AssemblyAreaSize.Y = 100.0f;
	AssemblyAreaSize.Z = 100.0f;
}

#if WITH_EDITOR
void UMS_StorageAssemblyAreaComponent::OnComponentCreated()
{
	Super::OnComponentCreated();

	DrawAssemblyAreaOutline();
}

void UMS_StorageAssemblyAreaComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	Super::OnComponentDestroyed(bDestroyingHierarchy);

	EraseAssemblyAreaOutline();
}

void UMS_StorageAssemblyAreaComponent::OnRegister()
{
	Super::OnRegister();

	RedrawAssemblyAreaOutline();
}

void UMS_StorageAssemblyAreaComponent::InitializeComponent()
{
	Super::InitializeComponent();

	if (GetOwner() == nullptr && Cast<AMS_Storage>(GetOwner()) != nullptr)
	{
		checkNoEntry();
	}

	OwnerStorage = Cast<AMS_Storage>(GetOwner());
}

void UMS_StorageAssemblyAreaComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	FName ChangedMemberPropertyName = (PropertyChangedEvent.MemberProperty != nullptr ? PropertyChangedEvent.MemberProperty->GetFName() : NAME_None);
	if (ChangedMemberPropertyName == FName("RelativeLocation") || ChangedMemberPropertyName == FName("RelativeRotation") || ChangedMemberPropertyName == FName("AssemblyAreaOutlineColor") || ChangedMemberPropertyName == FName("AssemblyAreaOutlineThickness"))
	{
		RedrawAssemblyAreaOutline();
	}
	else if (ChangedMemberPropertyName == FName("AssemblyAreaSize"))
	{
		RedrawAssemblyAreaOutline();
	}
}

void UMS_StorageAssemblyAreaComponent::PostEditComponentMove(bool bFinished)
{
	Super::PostEditComponentMove(bFinished);

	RedrawAssemblyAreaOutline();
}

void UMS_StorageAssemblyAreaComponent::PostEditUndo()
{
	Super::PostEditUndo();

	RedrawAssemblyAreaOutline();
}

void UMS_StorageAssemblyAreaComponent::DrawAssemblyAreaOutline()
{
	if (GetWorld() != nullptr)
	{
		GetWorld()->PersistentLineBatcher->DrawBox(GetComponentLocation(), AssemblyAreaSize / 2.0f, GetComponentRotation().Quaternion(), AssemblyAreaOutlineColor, -1.0f, SDPG_World, AssemblyAreaOutlineThickness, GetUniqueID());
	}
}

void UMS_StorageAssemblyAreaComponent::RedrawAssemblyAreaOutline()
{
	if (GetWorld() != nullptr)
	{
		GetWorld()->PersistentLineBatcher->ClearBatch(GetUniqueID());
		GetWorld()->PersistentLineBatcher->DrawBox(GetComponentLocation() + FVector(0.0f, 0.0f, AssemblyAreaSize.Z / 2.0f), AssemblyAreaSize / 2.0f, GetComponentRotation().Quaternion(), AssemblyAreaOutlineColor, -1.0f, SDPG_World, AssemblyAreaOutlineThickness, GetUniqueID());
	}
}

void UMS_StorageAssemblyAreaComponent::EraseAssemblyAreaOutline()
{
	if (GetWorld() != nullptr)
	{
		GetWorld()->PersistentLineBatcher->ClearBatch(GetUniqueID());
	}
}
#endif

FVector UMS_StorageAssemblyAreaComponent::FindAdjacentLocationWithBay(int aBayOrder, AMS_StaffAICharacter* aTarget)
{
	return GetComponentLocation();
}