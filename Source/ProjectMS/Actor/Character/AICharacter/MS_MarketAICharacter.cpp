// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_MarketAICharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Component/Actor/Character/MS_MovingBoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "ContentsUtilities/MS_LevelDefine.h"


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
	
	UCharacterMovementComponent* CharacterMovementComponent = Cast<UCharacterMovementComponent>(GetMovementComponent());
	if (CharacterMovementComponent)
	{
		CharacterMovementComponent->GravityScale = 0.f;
	}
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
}

void AMS_MarketAICharacter::SetWalkingDirectionAndPathLocation(EMS_Direction aWalkingDirection,
	FVector2D aPathLocation, bool aStopInPathLocation)
{
	if (PreviousPathLocation != PathLocation)
	{
		PreviousPathLocation = PathLocation;
	}
	
	WalkingDirection = aWalkingDirection;
	PathLocation = aPathLocation;
	bStopInPathLocation = aStopInPathLocation;
}

void AMS_MarketAICharacter::SetRocationByWalkingDirection(EMS_Direction aWalkingDirection)
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
	if (FMath::Abs((PathLocation - FVector2D(NewLocation.X, NewLocation.Y)).Length()) > FMath::Abs((PathLocation - PreviousPathLocation).Length()))
	{
		SetActorLocation(FVector(PathLocation.X, PathLocation.Y, NewLocation.Z));
		bool bBound = OnReachPathLocationDelegate.ExecuteIfBound(PathLocation);
		return;
	}
		
	if (bStopInPathLocation)
	{
		switch (WalkingDirection)
		{
		case EMS_Direction::Front :
			{
				if (NewLocation.Y <= PathLocation.Y)
				{
					NewLocation = FVector(PathLocation.X, PathLocation.Y, NewLocation.Z);
					bool bBound = OnReachPathLocationDelegate.ExecuteIfBound(PathLocation);
				}
				break;
			}

		case EMS_Direction::Back :
			{
				if (NewLocation.Y >= PathLocation.Y)
				{
					NewLocation = FVector(PathLocation.X, PathLocation.Y, NewLocation.Z);
					bool bBound = OnReachPathLocationDelegate.ExecuteIfBound(PathLocation);
				}
				break;
			}
				
		case EMS_Direction::Right :
			{
				if (NewLocation.X >= PathLocation.X)
				{
					NewLocation = FVector(PathLocation.X, PathLocation.Y, NewLocation.Z);
					bool bBound = OnReachPathLocationDelegate.ExecuteIfBound(PathLocation);
				}
				break;
			}

		case EMS_Direction::Left :
			{
				if (NewLocation.X <= PathLocation.X)
				{
					NewLocation = FVector(PathLocation.X, PathLocation.Y, NewLocation.Z);
					bool bBound = OnReachPathLocationDelegate.ExecuteIfBound(PathLocation);
				}
				break;
			}

		default:
			{
				break;
			}
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
