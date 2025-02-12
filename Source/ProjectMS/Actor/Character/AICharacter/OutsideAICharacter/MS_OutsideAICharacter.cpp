// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_OutsideAICharacter.h"

#include "MS_ActorUnitBase.h"
#include "MS_DuckSplineActor.h"
#include "MS_UnitBase.h"
#include "AI/AIController/OutsideAIController/MS_OutsideAIController.h"
#include "AI/AnimInstance/MS_AIAnimInstance.h"
#include "Manager_Both/MS_UnitManager.h"
#include "Units/MS_AIUnit.h"


// Sets default values
AMS_OutsideAICharacter::AMS_OutsideAICharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	AIControllerClass = AMS_OutsideAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AMS_OutsideAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

// Called when the game starts or when spawned
void AMS_OutsideAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
	NearestSpline = FindNearestSpline();
}

// Called every frame
void AMS_OutsideAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(AIAnimInstance.IsValid() && AIAnimInstance->IsActWalking() == false)
	{
		return;
	}
	
	if(NearestSpline.IsValid() && GetCharacterMovement())
	{
		const FVector CurrentVehicleLocation = GetActorLocation();
		const FVector TangentLocation = NearestSpline->FindTangentClosestToWorldLocation(CurrentVehicleLocation);
		const FRotator MoveNextRotation = TangentLocation.Rotation();
		const FVector ClosetLocation = NearestSpline->FindLocationClosestToWorldLocation(CurrentVehicleLocation);
		SetActorLocation(ClosetLocation + TangentLocation.GetSafeNormal() * DuckVelocity);
		SetActorRotation(MoveNextRotation);
	}
}

MS_Handle AMS_OutsideAICharacter::GetUnitHandle() const
{
	const TObjectPtr<UMS_AIUnit> AIUnit = Cast<UMS_AIUnit>(GetOuter());
	if(!AIUnit)
	{
		return INDEX_NONE;
	}

	return AIUnit->GetUnitHandle();
}

TObjectPtr<AMS_DuckSplineActor> AMS_OutsideAICharacter::FindNearestSpline() const
{
	TArray<TObjectPtr<UMS_UnitBase>> DuckSplineUnits; 
	gUnitMng.GetUnit(EMS_UnitType::DuckSpline, DuckSplineUnits);

	float DistanceMin = 0.f;
	TObjectPtr<UMS_ActorUnitBase> NearestSplineUnit = nullptr;
	
	for(const auto& SplineUnit : DuckSplineUnits)
	{
		if(const TObjectPtr<UMS_ActorUnitBase> SplineActorUnit = Cast<UMS_ActorUnitBase>(SplineUnit))
		{
			const float Distance = FVector::Distance(GetActorLocation(), SplineActorUnit->GetUnitPosition());
			if(DistanceMin == 0.f || DistanceMin > Distance)
			{
				DistanceMin = Distance;
				NearestSplineUnit = SplineActorUnit;
			}
		}
	}

	if(!NearestSplineUnit)
	{
		return nullptr;
	}

	TObjectPtr<AMS_DuckSplineActor> VehicleSplineActor = Cast<AMS_DuckSplineActor>(NearestSplineUnit->GetActor());
	return VehicleSplineActor;
}
