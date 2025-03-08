// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_OutsideAICharacter.h"

#include "MS_ActorUnitBase.h"
#include "MS_MarketFrontActor.h"
#include "MS_UnitBase.h"
#include "AI/AIController/OutsideAIController/MS_OutsideAIController.h"
#include "Animation/MS_AIAnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Manager_Both/MS_UnitManager.h"
#include "Prop/Spline/MS_DuckSplineActor.h"
#include "Units/MS_AIUnit.h"


AMS_OutsideAICharacter::AMS_OutsideAICharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	AIControllerClass = AMS_OutsideAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AMS_OutsideAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	TArray<AActor*> FrontDoorActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMS_MarketFrontActor::StaticClass(), FrontDoorActors);

	// if(FrontDoorActors.Num() != 1)
	// {
	// 	MS_LOG_VERBOSITY(Error, TEXT("MarketFrontActor has more than one. [ Confirmed number of actors : %d"), FrontDoorActors.Num());
	// 	MS_ENSURE(false);
	// }

	constexpr int32 FrontDoorIndex = 0;
	if(FrontDoorActors.IsValidIndex(FrontDoorIndex))
	{
		MarketFrontActor = Cast<AMS_MarketFrontActor>(FrontDoorActors[FrontDoorIndex]);
	}
}

void AMS_OutsideAICharacter::BeginPlay()
{
	Super::BeginPlay();

	NearestSpline = FindNearestSpline();
}

void AMS_OutsideAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(UMS_AIAnimInstance* AIAnimInstance = GetAIAnimInstance())
	{
		if(AIAnimInstance->IsActWalking() == false || AIAnimInstance->IsActFinished() == true)
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
	const TObjectPtr<UMS_AIUnit> AIUnit = Cast<UMS_AIUnit>(GetOwnerUnitBase());
	if(!AIUnit)
	{
		return INDEX_NONE;
	}

	return AIUnit->GetUnitHandle();
}

TObjectPtr<AMS_DuckSplineActor> AMS_OutsideAICharacter::FindNearestSpline() const
{
	TArray<TWeakObjectPtr<UMS_UnitBase>> DuckSplineUnits; 
	gUnitMng.GetUnits(EMS_UnitType::DuckSpline, DuckSplineUnits);

	float DistanceMin = 0.f;
	TWeakObjectPtr<UMS_ActorUnitBase> NearestSplineUnit = nullptr;
	
	for(const auto& SplineUnit : DuckSplineUnits)
	{
		if(UMS_ActorUnitBase* SplineActorUnit = Cast<UMS_ActorUnitBase>(SplineUnit))
		{
			const float Distance = FVector::Distance(GetActorLocation(), SplineActorUnit->GetUnitPosition());
			if(DistanceMin == 0.f || DistanceMin > Distance)
			{
				DistanceMin = Distance;
				NearestSplineUnit = SplineActorUnit;
			}
		}
	}

	if(NearestSplineUnit == nullptr)
	{
		return nullptr;
	}

	TObjectPtr<AMS_DuckSplineActor> DuckSplineActor = Cast<AMS_DuckSplineActor>(NearestSplineUnit->GetActor());
	return DuckSplineActor;
}
