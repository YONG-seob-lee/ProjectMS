#include "Component/Prop/MS_StorageOperationSpotComponent.h"

#include "Components/CapsuleComponent.h"
#include "Components/LineBatchComponent.h"

#include "Actor/Prop/Storage/MS_Prop_Storage.h"

UMS_StorageOperationSpotComponent::UMS_StorageOperationSpotComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	SpotSize.X = SpotSize.Y = 25.0f;
	SpotSize.Z = 5.0f;

	AssemblyAreaSize.X = 100.0f;
	AssemblyAreaSize.Y = 100.0f;
	AssemblyAreaSize.Z = 100.0f;
}


void UMS_StorageOperationSpotComponent::InitializeComponent()
{
	Super::InitializeComponent();

	OwnerStorage = Cast<AMS_Prop_Storage>(GetOwner());
	MS_CHECK(OwnerStorage);
}

#if WITH_EDITOR
void UMS_StorageOperationSpotComponent::OnComponentCreated()
{
	Super::OnComponentCreated();

	DrawSpotOutline();
	DrawAssemblyAreaOutline();
}

void UMS_StorageOperationSpotComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	Super::OnComponentDestroyed(bDestroyingHierarchy);

	EraseSpotOutline();
	EraseAssemblyAreaOutline();
}

void UMS_StorageOperationSpotComponent::OnRegister()
{
	Super::OnRegister();

	if (GetWorld() != nullptr)
	{
		GetWorld()->PersistentLineBatcher->ClearBatch(GetUniqueID());
	}

	RedrawSpotOutline();
	RedrawAssemblyAreaOutline();
}

void UMS_StorageOperationSpotComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	FName ChangedMemberPropertyName = (PropertyChangedEvent.MemberProperty != nullptr ? PropertyChangedEvent.MemberProperty->GetFName() : NAME_None);
	if (ChangedMemberPropertyName == FName("RelativeLocation") || ChangedMemberPropertyName == FName("RelativeRotation") || ChangedMemberPropertyName == FName("SpotOutlineColor") || ChangedMemberPropertyName == FName("SpotOutlineThickness") || ChangedMemberPropertyName == FName("AssemblyAreaOutlineColor") || ChangedMemberPropertyName == FName("AssemblyAreaOutlineThickness"))
	{
		if (GetWorld() != nullptr)
		{
			GetWorld()->PersistentLineBatcher->ClearBatch(GetUniqueID());
		}

		RedrawSpotOutline();
		RedrawAssemblyAreaOutline();
	}
	else if (ChangedMemberPropertyName == FName("SpotSize"))
	{
		if (GetWorld() != nullptr)
		{
			GetWorld()->PersistentLineBatcher->ClearBatch(GetUniqueID());
		}

		RedrawSpotOutline();
		RedrawAssemblyAreaOutline();
	}
}

void UMS_StorageOperationSpotComponent::PostEditComponentMove(bool bFinished)
{
	Super::PostEditComponentMove(bFinished);

	if (GetWorld() != nullptr)
	{
		GetWorld()->PersistentLineBatcher->ClearBatch(GetUniqueID());
	}

	RedrawSpotOutline();
	RedrawAssemblyAreaOutline();

}

void UMS_StorageOperationSpotComponent::PostEditUndo()
{
	Super::PostEditUndo();

	if (GetWorld() != nullptr)
	{
		GetWorld()->PersistentLineBatcher->ClearBatch(GetUniqueID());
	}

	RedrawSpotOutline();
	RedrawAssemblyAreaOutline();
}

void UMS_StorageOperationSpotComponent::DrawSpotOutline()
{
	if (GetWorld() != nullptr)
	{
		GetWorld()->PersistentLineBatcher->DrawCylinder(GetComponentLocation() + FVector(0.0f, 0.0f, SpotSize.Z), GetComponentLocation(), (SpotSize.X + SpotSize.Y) / 4.0f, 8, SpotOutlineColor, -1.0f, SDPG_World, SpotOutlineThickness, GetUniqueID());
	}
}

void UMS_StorageOperationSpotComponent::RedrawSpotOutline()
{
	if (GetWorld() != nullptr)
	{
		GetWorld()->PersistentLineBatcher->DrawCylinder(GetComponentLocation() + FVector(0.0f, 0.0f, SpotSize.Z), GetComponentLocation(), (SpotSize.X + SpotSize.Y) / 4.0f, 8, SpotOutlineColor, -1.0f, SDPG_World, SpotOutlineThickness, GetUniqueID());
	}
}

void UMS_StorageOperationSpotComponent::EraseSpotOutline()
{
	if (GetWorld() != nullptr)
	{
		GetWorld()->PersistentLineBatcher->ClearBatch(GetUniqueID());
	}
}

void UMS_StorageOperationSpotComponent::DrawAssemblyAreaOutline()
{
	if (GetWorld() != nullptr)
	{
		GetWorld()->PersistentLineBatcher->DrawBox(GetComponentLocation(), AssemblyAreaSize / 2.0f, GetComponentRotation().Quaternion(), AssemblyAreaOutlineColor, -1.0f, SDPG_World, AssemblyAreaOutlineThickness, GetUniqueID());
	}
}

void UMS_StorageOperationSpotComponent::RedrawAssemblyAreaOutline()
{
	if (GetWorld() != nullptr)
	{
		GetWorld()->PersistentLineBatcher->DrawBox(GetComponentLocation() + FVector(0.0f, 0.0f, AssemblyAreaSize.Z / 2.0f), AssemblyAreaSize / 2.0f, GetComponentRotation().Quaternion(), AssemblyAreaOutlineColor, -1.0f, SDPG_World, AssemblyAreaOutlineThickness, GetUniqueID());
	}
}

void UMS_StorageOperationSpotComponent::EraseAssemblyAreaOutline()
{
	if (GetWorld() != nullptr)
	{
		GetWorld()->PersistentLineBatcher->ClearBatch(GetUniqueID());
	}
}

#endif

void UMS_StorageOperationSpotComponent::ReserveWorker(AMS_StaffAICharacter* aStaffCharacter)
{
	ReservationFlag = true;
	ReservationWorker = aStaffCharacter;
}

void UMS_StorageOperationSpotComponent::UnreserveWorker()
{
	ReservationFlag = false;
	ReservationWorker = nullptr;
}

void UMS_StorageOperationSpotComponent::DeployWorker(AMS_StaffAICharacter* aStaffCharacter)
{
	OccupancyFlag = true;
	OccupancyWorker = aStaffCharacter;
}

void UMS_StorageOperationSpotComponent::UndeployWorker()
{
	OccupancyFlag = false;
	OccupancyWorker = nullptr;
}
