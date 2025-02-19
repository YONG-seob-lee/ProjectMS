// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_MarketAICharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Component/Actor/Character/MS_MovingBoxComponent.h"
#include "Components/CapsuleComponent.h"


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
}

void AMS_MarketAICharacter::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);

	if (WalkingDirection != EMS_Direction::None)
	{
		CacheLocation = GetActorLocation();

		FVector DirectionVector = UMS_MathUtility::ConvertDirectionToVector(WalkingDirection);
		FRotator DirectionRotator = UMS_MathUtility::ConvertDirectionToRotator(WalkingDirection);
		
		FVector NewLocation = GetActorLocation() + DirectionVector * DuckVelocity * aDeltaTime;
		
		if (bStopInPathLocation)
		{
			switch (WalkingDirection)
			{
			case EMS_Direction::Front :
				{
					if (NewLocation.Y < PathLocation.Y)
					{
						NewLocation = FVector(PathLocation.X, PathLocation.Y, NewLocation.Z);
					}
					break;
				}

			case EMS_Direction::Back :
				{
					if (NewLocation.Y > PathLocation.Y)
					{
						NewLocation = FVector(PathLocation.X, PathLocation.Y, NewLocation.Z);
					}
					break;
				}
				
			case EMS_Direction::Right :
				{
					if (NewLocation.X > PathLocation.X)
					{
						NewLocation = FVector(PathLocation.X, PathLocation.Y, NewLocation.Z);
					}
					break;
				}

			case EMS_Direction::Left :
				{
					if (NewLocation.X < PathLocation.X)
					{
						NewLocation = FVector(PathLocation.X, PathLocation.Y, NewLocation.Z);
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
		SetActorRotation(DirectionRotator);
	}
}

void AMS_MarketAICharacter::SetWalkingDirection(EMS_Direction aWalkingDirection,
	FVector2D aPathLocation, bool aStopInPathLocation)
{
	WalkingDirection = aWalkingDirection;
	PathLocation = aPathLocation;
	bStopInPathLocation = aStopInPathLocation;
}
