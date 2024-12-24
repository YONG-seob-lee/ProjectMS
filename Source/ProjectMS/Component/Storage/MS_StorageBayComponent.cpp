#include "Component/Storage/MS_StorageBayComponent.h"

#include "Components/CapsuleComponent.h"
#include "Components/LineBatchComponent.h"

#include "Actor/Character/AICharacter/StaffAICharacter/MS_StaffAICharacter.h"
#include "Actor/Storage/MS_Storage.h"

UMS_StorageBayComponent::UMS_StorageBayComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bWantsInitializeComponent = true;

	BaySize.X = BaySize.Y = 25.0f;
	BaySize.Z = 5.0f;
}

#if WITH_EDITOR
void UMS_StorageBayComponent::OnComponentCreated()
{
	Super::OnComponentCreated();

	DrawBayOutline();
}

void UMS_StorageBayComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	Super::OnComponentDestroyed(bDestroyingHierarchy);

	EraseBayOutline();
}

void UMS_StorageBayComponent::OnRegister()
{
	Super::OnRegister();

	RedrawBayOutline();
}

void UMS_StorageBayComponent::InitializeComponent()
{
	Super::InitializeComponent();

	if (GetOwner() == nullptr && Cast<AMS_Storage>(GetOwner()) != nullptr)
	{
		checkNoEntry();
	}

	OwnerStorage = Cast<AMS_Storage>(GetOwner());
}

void UMS_StorageBayComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	FName ChangedMemberPropertyName = (PropertyChangedEvent.MemberProperty != nullptr ? PropertyChangedEvent.MemberProperty->GetFName() : NAME_None);
	if (ChangedMemberPropertyName == FName("RelativeLocation") || ChangedMemberPropertyName == FName("RelativeRotation") || ChangedMemberPropertyName == FName("BayOutlineColor") || ChangedMemberPropertyName == FName("BayOutlineThickness"))
	{
		RedrawBayOutline();
	}
	else if (ChangedMemberPropertyName == FName("BaySize"))
	{
		RedrawBayOutline();
	}
}

void UMS_StorageBayComponent::PostEditComponentMove(bool bFinished)
{
	Super::PostEditComponentMove(bFinished);

	RedrawBayOutline();
}

void UMS_StorageBayComponent::PostEditUndo()
{
	Super::PostEditUndo();

	RedrawBayOutline();
}

void UMS_StorageBayComponent::DrawBayOutline()
{
	if (GetWorld() != nullptr)
	{
		GetWorld()->PersistentLineBatcher->DrawCylinder(GetComponentLocation() + FVector(0.0f, 0.0f, BaySize.Z), GetComponentLocation(), (BaySize.X + BaySize.Y) / 4.0f, 8, BayOutlineColor, -1.0f, SDPG_World, BayOutlineThickness, GetUniqueID());
	}
}

void UMS_StorageBayComponent::RedrawBayOutline()
{
	if (GetWorld() != nullptr)
	{
		GetWorld()->PersistentLineBatcher->ClearBatch(GetUniqueID());
		GetWorld()->PersistentLineBatcher->DrawCylinder(GetComponentLocation() + FVector(0.0f, 0.0f, BaySize.Z), GetComponentLocation(), (BaySize.X + BaySize.Y) / 4.0f, 8, BayOutlineColor, -1.0f, SDPG_World, BayOutlineThickness, GetUniqueID());
	}
}

void UMS_StorageBayComponent::EraseBayOutline()
{
	if (GetWorld() != nullptr)
	{
		GetWorld()->PersistentLineBatcher->ClearBatch(GetUniqueID());
	}
}
#endif

void UMS_StorageBayComponent::ReserveWorker(AMS_StaffAICharacter* aTarget)
{
	ReservationFlag = true;
	ReservationWorker = aTarget;
}

void UMS_StorageBayComponent::UnreserveWorker()
{
	ReservationFlag = false;
	ReservationWorker = nullptr;
}

void UMS_StorageBayComponent::DeployWorker(AMS_StaffAICharacter* aTarget)
{
	if (aTarget->GetRootComponent()->GetAttachParent() != nullptr)
		return;

	aTarget->CollisionCapsuleComponent->SetCollisionProfileName("StorageWorkerCollisionPreset");
	aTarget->AttachToComponent(this, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false));
	float ScaledCollisionRadius = {}, ScaledCollisionHalfHeight = {};
	aTarget->CollisionCapsuleComponent->GetScaledCapsuleSize(ScaledCollisionRadius, ScaledCollisionHalfHeight);
	aTarget->GetRootComponent()->SetRelativeLocation(FVector(0.0f, 0.0f, ScaledCollisionHalfHeight));
	aTarget->GetRootComponent()->SetRelativeRotation(FRotator::ZeroRotator);
	aTarget->TargetStorageBayOrder = BayOrder;
	OccupancyFlag = true;
	OccupancyWorker = aTarget;
}

void UMS_StorageBayComponent::UndeployWorker()
{
	const TArray<TObjectPtr<USceneComponent>>& AttachChildComponentArray = GetAttachChildren();
	if (AttachChildComponentArray.Num() == 0)
		return;

	AMS_StaffAICharacter* Target = Cast<AMS_StaffAICharacter>(AttachChildComponentArray[0]->GetOwner());
	Target->DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepWorld, false));
	// Target->SetActorLocation(OwnerInst->StorageAssemblyAreaComponent->FindAdjacentLocationWithBay(BayOrder, Target));
	Target->CollisionCapsuleComponent->SetCollisionProfileName("StaffCollisionPreset");
	Target->TargetStorageBayOrder = INT_MIN;
	OccupancyFlag = false;
	OccupancyWorker = nullptr;
}
