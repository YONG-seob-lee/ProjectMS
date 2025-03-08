// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_MarketAICharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Component/Actor/Character/MS_MovingBoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "ContentsUtilities/MS_LevelDefine.h"
#include "Actor/Equipment/MS_Equipment.h"
#include "Animation/Market/MS_MarketAIAnimInstance.h"
#include "Components/WidgetComponent.h"
#include "ContentsUtilities/MS_AIDefine.h"
#include "Engine/SkeletalMeshSocket.h"


AMS_MarketAICharacter::AMS_MarketAICharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	if (GetCapsuleComponent())
	{
		GetCapsuleComponent()->SetCollisionProfileName(TEXT("ClickableShape"));
	}

	if (GetMesh())
	{
		GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	}
	
	UCharacterMovementComponent* CharacterMovementComponent = GetCharacterMovement();
	if (CharacterMovementComponent)
	{
		CharacterMovementComponent->GravityScale = 0.f;
	}

	SkinCapMesh = CreateDefaultSubobject<USkeletalMeshComponent>("SkinCapMesh");
	if(SkinCapMesh)
	{
		SkinCapMesh->SetupAttachment(GetMesh());
	}

	SkinTopMesh = CreateDefaultSubobject<USkeletalMeshComponent>("SkinTopMesh");
	if(SkinTopMesh)
	{
		SkinTopMesh->SetupAttachment(GetMesh());
	}
	
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	if(WidgetComponent)
	{
		WidgetComponent->SetVisibility(false);
	}
	
	AIParameterComponent = CreateDefaultSubobject<UMS_AIParameterComponent>(TEXT("AIParameterComponent"));
}

void AMS_MarketAICharacter::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	// Component
	GetComponents<UMS_MovingBoxComponent>(MovingBoxComponents);

	// Component
	TArray<UPrimitiveComponent*> PrimitiveComponents;
	GetComponents<UPrimitiveComponent>(PrimitiveComponents);

	// Physics off
	for (UPrimitiveComponent* PrimitiveComponent : PrimitiveComponents)
	{
		PrimitiveComponent->SetSimulatePhysics(false);
		PrimitiveComponent->SetEnableGravity(false);
	}

	// Z 위치 보정
	if (GetCapsuleComponent())
    {
		FVector Location = GetActorLocation();
    	float LocationZ = GetCapsuleComponent()->GetScaledCapsuleHalfHeight();

		SetActorLocation(FVector(Location.X, Location.Y, LocationZ));
    }
}

void AMS_MarketAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// Physics off
	TArray<UPrimitiveComponent*> PrimitiveComponents;
	GetComponents<UPrimitiveComponent>(PrimitiveComponents);
	
	for (UPrimitiveComponent* PrimitiveComponent : PrimitiveComponents)
	{
		PrimitiveComponent->SetSimulatePhysics(false);
		PrimitiveComponent->SetEnableGravity(false);
	}

	// Z 위치 보정
	if (GetCapsuleComponent())
	{
		FVector Location = GetActorLocation();
		float LocationZ = GetCapsuleComponent()->GetScaledCapsuleHalfHeight();

		SetActorLocation(FVector(Location.X, Location.Y, LocationZ));
	}

	// Equipment
	SpawnAllEquipment();	// 비용 절감을 미리 스폰
	
	const TObjectPtr<UMS_MarketAIAnimInstance> MarketAIAnimInstance = Cast<UMS_MarketAIAnimInstance>(GetAIAnimInstance());
	if(MarketAIAnimInstance)
	{
		MarketAIAnimInstance->OnChangeInActionDelegate.AddUObject(this, &AMS_MarketAICharacter::OnChangeAnimationInAction);
	}
}

void AMS_MarketAICharacter::BeginPlay()
{
	Super::BeginPlay();

	PreviousPathLocation = FVector2D(GetActorLocation().X, GetActorLocation().Y);
}

void AMS_MarketAICharacter::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
	
	if (WalkingDirection != EMS_Direction::None)
	{
		UpdateLocation(aDeltaTime);
		UpdateRotation(aDeltaTime);
	}

	if(bIsChatting == false)
	{
		if(const TObjectPtr<UMS_SpeechBubbleWidget> SpeechBubble = Cast<UMS_SpeechBubbleWidget>(WidgetComponent->GetWidget()))
		{
			if(SpeechBubble->bIsConstructed && SpeechBubble->IsPlayingAnimation() == false)
			{
				SpeechBubble->PlaySpeech();
				bIsChatting = true;
			}
		}
	}
	WidgetComponent->SetWorldLocation(GetActorLocation() + FVector(0.f, -50.f, 0.f));
}

void AMS_MarketAICharacter::PostInitialize(MS_Handle aUnitHandle) const
{
	if(AIParameterComponent)
	{
		AIParameterComponent->Initialize(aUnitHandle);
	}
}

void AMS_MarketAICharacter::SetWalkingDirectionAndPathLocation(EMS_Direction aWalkingDirection,
																FVector2D aPathLocation, bool aStopInPathLocation)
{
	if (PathLocation != aPathLocation)
	{
		PreviousPathLocation = PathLocation;
	}
	
	WalkingDirection = aWalkingDirection;
	PathLocation = aPathLocation;
	bStopInPathLocation = aStopInPathLocation;
}

void AMS_MarketAICharacter::SetRotationByWalkingDirection(EMS_Direction aWalkingDirection)
{
	WalkingDirection = aWalkingDirection;
	PathLocation = FVector2D::ZeroVector;
	bStopInPathLocation = false;

	FRotator Rotator = UMS_MathUtility::ConvertDirectionToRotator(WalkingDirection);
	SetActorRotation(Rotator);
}

void AMS_MarketAICharacter::UpdateLocation(float aDeltaTime)
{
	FVector CurrentLocation = GetActorLocation();
		
	FVector DirectionVector = UMS_MathUtility::ConvertDirectionToVector(WalkingDirection);
	
	FVector NewLocation = CurrentLocation + DirectionVector * DuckVelocity * aDeltaTime;

	// 프레임 드랍으로 경로를 벗어났을때 위치 이동
	// ToDo : 보완 및 버그로 인해 PathLocation이 유효하지 않을 때 검사 필요
	if (FMath::Abs((PathLocation - FVector2D(NewLocation.X, NewLocation.Y)).Length()) >
		FMath::Max(MS_GridSize.X, FMath::Abs((PathLocation - PreviousPathLocation).Length())) * 4.f)
	{

		SetActorLocation(FVector(PathLocation.X, PathLocation.Y, NewLocation.Z));
		bool bBound = OnReachPathLocationDelegate.ExecuteIfBound(PathLocation);
		return;
	}
	
	switch (WalkingDirection)
	{
		/* IsRotationComplete() : 로케이션이 완료 되어야 도착 판정.
		 * 로케이션이 완료되지 않으면 완료될 때까지 매 틱 이곳에서 IsRocationComplete를 호출.
		 * 따라서 UpdateRocation 쪽에서 따로 Location Complete를 검증할 필요는 없다.
		 */
	case EMS_Direction::Front :
		{
			if (NewLocation.Y >= PathLocation.Y)
			{
				if (bStopInPathLocation)
				{
					NewLocation = FVector(PathLocation.X, PathLocation.Y, NewLocation.Z);
				}

				if (!IsRotationComplete())
				{
					return;
				}

				bool bBound = OnReachPathLocationDelegate.ExecuteIfBound(PathLocation);
			}
			break;
		}

	case EMS_Direction::Back :
		{
			if (NewLocation.Y <= PathLocation.Y)
			{
				if (bStopInPathLocation)
				{
					NewLocation = FVector(PathLocation.X, PathLocation.Y, NewLocation.Z);
				}

				if (!IsRotationComplete())
				{
					return;
				}

				bool bBound = OnReachPathLocationDelegate.ExecuteIfBound(PathLocation);
			}
			break;
		}
			
	case EMS_Direction::Right :
		{
			if (NewLocation.X >= PathLocation.X)
			{
				if (bStopInPathLocation)
				{
					NewLocation = FVector(PathLocation.X, PathLocation.Y, NewLocation.Z);
				}

				if (!IsRotationComplete())
				{
					return;
				}

				bool bBound = OnReachPathLocationDelegate.ExecuteIfBound(PathLocation);
			}
			break;
		}

	case EMS_Direction::Left :
		{
			if (NewLocation.X <= PathLocation.X)
			{
				if (bStopInPathLocation)
				{
					NewLocation = FVector(PathLocation.X, PathLocation.Y, NewLocation.Z);
				}

				if (!IsRotationComplete())
				{
					return;
				}

				bool bBound = OnReachPathLocationDelegate.ExecuteIfBound(PathLocation);
			}
			break;
		}

	default:
		{
			break;
		}
	}
	
		
	SetActorLocation(NewLocation);
}

void AMS_MarketAICharacter::UpdateRotation(float aDeltaTime)
{
	float CurrentRotatorYaw = GetActorRotation().Yaw;
	if (CurrentRotatorYaw < 0.f)
	{
		CurrentRotatorYaw += 360.f;
	}
	
	FRotator DirectionRotator = UMS_MathUtility::ConvertDirectionToRotator(WalkingDirection);
		
	if (CurrentRotatorYaw != DirectionRotator.Yaw)
	{
		bool bRotationClockwise = UMS_MathUtility::IsRotationClockwise(CurrentRotatorYaw, DirectionRotator.Yaw);
		float SignFactor = bRotationClockwise ? 1.f : -1.f;
		float NewRotatorYaw = CurrentRotatorYaw + SignFactor * DuckRotateVelocity * aDeltaTime;
		if (NewRotatorYaw < 0.f)
		{
			NewRotatorYaw += 360.f;
		}

		if (bRotationClockwise)
		{
			if (WalkingDirection == EMS_Direction::Front)
			{
				if (NewRotatorYaw < CurrentRotatorYaw)
				{
					NewRotatorYaw = DirectionRotator.Yaw;
				}
			}
			else
			{
				if (NewRotatorYaw > DirectionRotator.Yaw)
				{
					NewRotatorYaw = DirectionRotator.Yaw;
				}
			}
		}
		else
		{
			if (WalkingDirection == EMS_Direction::Front)
			{
				if (NewRotatorYaw > CurrentRotatorYaw)
				{
					NewRotatorYaw = DirectionRotator.Yaw;
				}
			}
			else
			{
				if (NewRotatorYaw < DirectionRotator.Yaw)
				{
					NewRotatorYaw = DirectionRotator.Yaw;
				}
			}
		}
			
		SetActorRotation(FRotator(0.f, NewRotatorYaw, 0.f));
	}
}

bool AMS_MarketAICharacter::IsRotationComplete() const
{
	float DirectionRotatorYaw = UMS_MathUtility::ConvertDirectionToRotator(WalkingDirection).Yaw;
	float CurrentRotatorYaw = GetActorRotation().Yaw;
	if (CurrentRotatorYaw < 0.f)
	{
		CurrentRotatorYaw += 360.f;
	}
	
	return FMath::IsNearlyEqual(DirectionRotatorYaw, CurrentRotatorYaw, MS_ERROR_TOLERANCE);
}

void AMS_MarketAICharacter::OnChangeCurrentSlotDatas(const TArray<FMS_SlotData>& aSlotDatas)
{
}

void AMS_MarketAICharacter::SpawnAllEquipment()
{
	for (auto& EquipmentClass : EquipmentClasses)
	{
		AMS_Equipment* SpawnEquipment = GetWorld()->SpawnActor<AMS_Equipment>(EquipmentClass.Value);
		
		const USkeletalMeshSocket* EquipmentSocket = GetMesh()->GetSocketByName(SocketName::Equipment);

		if (SpawnEquipment)
		{
			if (EquipmentSocket)
			{
				EquipmentSocket->AttachActor(SpawnEquipment, GetMesh());
			}
			else
			{
				MS_ENSURE(false);
			}
			
			Equipments.Emplace(EquipmentClass.Key, SpawnEquipment);
		}
		else
		{
			MS_ENSURE(false);
		}
	}

	UpdateShowEquipment();
}

void AMS_MarketAICharacter::Equip(const FName& aEquipmentName)
{
	if (!Equipments.Contains(aEquipmentName))
	{
		MS_ENSURE(false);
		return;
	}

	CurrentEquipmentName = aEquipmentName;

	UpdateShowEquipment();

	const TObjectPtr<UMS_MarketAIAnimInstance> MarketAIAnimInstance = Cast<UMS_MarketAIAnimInstance>(GetAIAnimInstance());
	if(MarketAIAnimInstance)
	{
		MarketAIAnimInstance->SetEquipmentName(CurrentEquipmentName);
	}
}

void AMS_MarketAICharacter::UnEquip()
{
	CurrentEquipmentName = FName();
	
	UpdateShowEquipment();

	const TObjectPtr<UMS_MarketAIAnimInstance> MarketAIAnimInstance = Cast<UMS_MarketAIAnimInstance>(GetAIAnimInstance());
	if(MarketAIAnimInstance)
	{
		MarketAIAnimInstance->SetEquipmentName(FName());
	}
}

void AMS_MarketAICharacter::OnChangeAnimationInAction(bool bInAction)
{
	bShowEquipment = !bInAction;

	UpdateShowEquipment();
}

void AMS_MarketAICharacter::UpdateShowEquipment()
{
	for (auto& Equipment : Equipments)
	{
		if (!IsValid(Equipment.Value))
		{
			MS_ENSURE(false);
			continue;
		}
		
		if (bShowEquipment && Equipment.Key == CurrentEquipmentName)
		{
			Equipment.Value->ShowEquipment(true);
		}
		else
		{
			Equipment.Value->ShowEquipment(false);
		}
	}
}

void AMS_MarketAICharacter::SetSkin(const FName& aCapName, const FName& aTopName)
{
	TObjectPtr<USkeletalMesh>* CapMesh = SkinCaps.Find(aCapName);
	if (CapMesh != nullptr && *CapMesh != nullptr)
	{
		SkinCapMesh->SetSkeletalMesh(*CapMesh);
		SkinCapMesh->SetVisibility(true);
		SkinCapMesh->SetLeaderPoseComponent(GetMesh());
	}
	else
	{
		SkinCapMesh->SetSkeletalMesh(nullptr);
		SkinCapMesh->SetVisibility(false);
	}

	TObjectPtr<USkeletalMesh>* TopMesh = SkinTops.Find(aTopName);
	if (TopMesh != nullptr && *TopMesh != nullptr)
	{
		SkinTopMesh->SetSkeletalMesh(*TopMesh);
		SkinTopMesh->SetVisibility(true);
		SkinTopMesh->SetLeaderPoseComponent(GetMesh());
	}
	else
	{
		SkinTopMesh->SetSkeletalMesh(nullptr);
		SkinTopMesh->SetVisibility(false);
	}
}

void AMS_MarketAICharacter::ShowChatting(EMS_ChattingType ChattingType) const
{
	FText Chatting = FText();

	EMS_ChattingType RandomType = ChattingType;
	if(RandomType == EMS_ChattingType::Undefined)
	{
		RandomType = static_cast<EMS_ChattingType>(FMath::RandRange(
		static_cast<int32>(EMS_ChattingType::PriceTooExpensive)
		, static_cast<int32>(EMS_ChattingType::ThereIsItem)));
	}
	
	if(AIParameterComponent)
	{
		AIParameterComponent->ChattingTrigger(RandomType, Chatting, FText(),FText());
	}
	
	if(WidgetComponent)
	{
		WidgetComponent->SetVisibility(true);
		if(const TObjectPtr<UMS_SpeechBubbleWidget> SpeechBubble = Cast<UMS_SpeechBubbleWidget>(WidgetComponent->GetWidget()))
		{
			SpeechBubble->StopAllAnimations();
			SpeechBubble->SetText(Chatting);
			SpeechBubble->SetOnFinishedSpeechFunc([this]()
			{
				WidgetComponent->SetVisibility(false);
			});
		}
	}
}

void AMS_MarketAICharacter::ShowImage(EMS_SpeechImageType SpeechImageType) const
{
	FText Chatting = FText();
	// if(AIParameterComponent)
	// {
	// 	AIParameterComponent->ChattingTrigger(aChattingType, Chatting, FText(),FText());
	// }
	
	if(WidgetComponent)
	{
		WidgetComponent->SetVisibility(true);
		if(const TObjectPtr<UMS_SpeechBubbleWidget> SpeechBubble = Cast<UMS_SpeechBubbleWidget>(WidgetComponent->GetWidget()))
		{
			SpeechBubble->SetImage(SpeechImageType);
			SpeechBubble->SetOnFinishedSpeechFunc([this]()
			{
				WidgetComponent->SetVisibility(false);
			});
		}
	}
}

void AMS_MarketAICharacter::ResetChatting()
{
	if(const TObjectPtr<UMS_SpeechBubbleWidget> SpeechBubble = Cast<UMS_SpeechBubbleWidget>(WidgetComponent->GetWidget()))
	{
		SpeechBubble->StopAllAnimations();
	}
	bIsChatting = false;
}

void AMS_MarketAICharacter::EventBehavior(EMS_BehaviorType aBehaviorType) const
{
	if(AIParameterComponent)
	{
		AIParameterComponent->BehaviorTrigger(aBehaviorType);
	}
}

void AMS_MarketAICharacter::EventPurchase(const TMap<int32, int32>& PurchaseItems) const
{
	if(AIParameterComponent)
	{
		for(const auto& PurchaseItem : PurchaseItems)
		{
			AIParameterComponent->PurchaseTrigger(PurchaseItem.Key, PurchaseItem.Value);
		}
	}
}
