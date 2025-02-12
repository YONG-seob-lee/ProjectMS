// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_StageLevelScriptActor.h"

#include "MS_Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Manager_Both/MS_UnitManager.h"
#include "Manager_Client/MS_InputManager.h"
#include "Manager_Client/MS_PlayerCameraManager.h"
#include "SpawnPoint/MS_OutsideDuckSpawnPoint.h"
#include "Units/MS_SplineUnit.h"
#include "Actor/Character/AICharacter/OutsideAICharacter/MS_DuckSplineActor.h"
#include "Vehicle/MS_VehicleSplineActor.h"


// Sets default values
AMS_StageLevelScriptActor::AMS_StageLevelScriptActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AMS_StageLevelScriptActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	ParsingCarSplineActors();
	ParsingDuckSplineActors();

	CollectOutsideDickSpawnPoint();
}

// Called when the game starts or when spawned
void AMS_StageLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();
	
	gInputMng.OnPointerDownDelegate.AddDynamic(this, &AMS_StageLevelScriptActor::OnPressDownEvent);
	gInputMng.OnPointerUpDelegate.AddDynamic(this, &AMS_StageLevelScriptActor::OnPressUpEvent);

	gCameraMng.LocateCamera(FVector(12600.f, -6380.f, 3200.f), EMS_ViewCameraType::QuarterView);
	gCameraMng.LocateCamera(FVector(13310.f, -8000.f, 390.f), EMS_ViewCameraType::SideView);
}

void AMS_StageLevelScriptActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	gInputMng.OnPointerDownDelegate.RemoveAll(this);
	gInputMng.OnPointerUpDelegate.RemoveAll(this);

	DestroySplineActors();
	
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void AMS_StageLevelScriptActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMS_StageLevelScriptActor::Destroyed()
{	
	Super::Destroyed();
}

void AMS_StageLevelScriptActor::CollectOutsideDickSpawnPoint()
{
	TArray<AActor*> DuckSpawnPoints;
	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMS_OutsideDuckSpawnPoint::StaticClass(), DuckSpawnPoints);

	for(AActor* SpawnPoint : DuckSpawnPoints)
	{
		AMS_OutsideDuckSpawnPoint* DuckSpawnPoint = Cast<AMS_OutsideDuckSpawnPoint>(SpawnPoint);
		if(!DuckSpawnPoint)
		{
			return;
		}

		gUnitMng.CreateUnit(EMS_UnitType::AI, 0,true, DuckSpawnPoint->GetSpawnLocation(), DuckSpawnPoint->GetSpawnRotation());
	}
}

void AMS_StageLevelScriptActor::ParsingCarSplineActors() const
{
	TArray<AActor*> SplineActors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMS_VehicleSplineActor::StaticClass(), SplineActors);
	
	for (AActor* Spline : SplineActors)
	{
		AMS_VehicleSplineActor* SplineActor = Cast<AMS_VehicleSplineActor>(Spline);
		if(!SplineActor)
		{
			MS_LOG_VERBOSITY(Error, TEXT("Error Spline Actor Casting. Check AMS_VehicleSplineActor"));
			return;
		}
		TObjectPtr<UMS_SplineUnit> SplineUnit = Cast<UMS_SplineUnit>(gUnitMng.CreateUnit(EMS_UnitType::CarSpline, INDEX_NONE, false));
		 if (IsValid(SplineUnit))
		 {
		 	// Set Unit Actor
		 	if (!SplineUnit->SetUnitActor(SplineActor))
		 	{
		 		MS_LOG_VERBOSITY(Error, TEXT("[%s] Set Unit Actor Fail"), *MS_FUNC_STRING);
		 		MS_ENSURE(false);
		 	}
		 }
		 else
		 {
		 	MS_LOG_VERBOSITY(Error, TEXT("[%s] Create Unit Fail"), *MS_FUNC_STRING);
		 	MS_ENSURE(false);
		 }
	}
}

void AMS_StageLevelScriptActor::ParsingDuckSplineActors() const
{
	TArray<AActor*> SplineActors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMS_DuckSplineActor::StaticClass(), SplineActors);
	
	for (AActor* Spline : SplineActors)
	{
		AMS_DuckSplineActor* SplineActor = Cast<AMS_DuckSplineActor>(Spline);
		if(!SplineActor)
		{
			MS_LOG_VERBOSITY(Error, TEXT("Error Spline Actor Casting. Check AMS_DuckSplineActor"));
			return;
		}
		TObjectPtr<UMS_SplineUnit> SplineUnit = Cast<UMS_SplineUnit>(gUnitMng.CreateUnit(EMS_UnitType::DuckSpline, INDEX_NONE, false));
		if (IsValid(SplineUnit))
		{
			// Set Unit Actor
			if (!SplineUnit->SetUnitActor(SplineActor))
			{
				MS_LOG_VERBOSITY(Error, TEXT("[%s] Set Unit Actor Fail"), *MS_FUNC_STRING);
				MS_ENSURE(false);
			}
		}
		else
		{
			MS_LOG_VERBOSITY(Error, TEXT("[%s] Create Unit Fail"), *MS_FUNC_STRING);
			MS_ENSURE(false);
		}
	}
}

void AMS_StageLevelScriptActor::DestroySplineActors()
{
	TArray<TObjectPtr<UMS_UnitBase>> DestroyUnits;
	gUnitMng.GetUnit(EMS_UnitType::CarSpline, DestroyUnits);
	gUnitMng.DestroyUnits(DestroyUnits);

	DestroyUnits.Empty();
	gUnitMng.GetUnit(EMS_UnitType::DuckSpline, DestroyUnits);
	gUnitMng.DestroyUnits(DestroyUnits);
}

void AMS_StageLevelScriptActor::OnPressDownEvent(FVector2D aPointerDownPosition, const FHitResult& aInteractableHitResult)
{
	AActor* PointerDownActor = aInteractableHitResult.GetActor();
	if(IsValid(PointerDownActor))
	{
		if(const TObjectPtr<AMS_Actor> TargetActor = Cast<AMS_Actor>(PointerDownActor))
		{
			if(TargetActor->HasInteractionComponent())
			{
				TargetActor->OnPressDownEvent();
			}
		}
	}
}

void AMS_StageLevelScriptActor::OnPressUpEvent(FVector2D aPointerUpPosition, const FHitResult& aInteractableHitResult)
{
	AActor* PointerUpActor = aInteractableHitResult.GetActor();
	if(IsValid(PointerUpActor))
	{
		if(const TObjectPtr<AMS_Actor> TargetActor = Cast<AMS_Actor>(PointerUpActor))
		{
			if(TargetActor->HasInteractionComponent())
			{
				TargetActor->OnPressUpEvent();
			}
		}
	}
}

