// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_CustomerSupervisor.h"

#include "MS_UnitBase.h"
#include "ContentsUtilities/MS_GameProcessDefine.h"
#include "Kismet/GameplayStatics.h"
#include "Manager_Both/MS_UnitManager.h"
#include "Prop/Spline/MS_CustomerSplineActor.h"
#include "SpawnPoint/MS_CustomerSpawnPoint.h"
#include "Units/MS_CustomerAIUnit.h"
#include "Units/MS_SplineUnit.h"


UMS_CustomerSupervisor::UMS_CustomerSupervisor()
{
}

void UMS_CustomerSupervisor::Initialize()
{
	Super::Initialize();
}

void UMS_CustomerSupervisor::Finalize()
{
	Super::Finalize();
}

void UMS_CustomerSupervisor::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);

	if(bStartCustomerSpawn)
	{
		if(CustomerAIUnits.Num() >= Customer::SpawnMaxUnitCount)
		{
			return;
		}
		
		if(SpawnIntervalDelayTime >= Customer::SpawnMaxTime)
		{
			SpawnCustomer();
			SpawnIntervalDelayTime = 0.f;
			return;
		}
		
		SpawnIntervalDelayTime += aDeltaTime;
	}
}

void UMS_CustomerSupervisor::Begin()
{
	Super::Begin();

	InitCustomerSpawnPoint();
	CashingDuckSplineActors();
}

void UMS_CustomerSupervisor::Exit()
{
	Super::Exit();
}

void UMS_CustomerSupervisor::UpdateMinute(int32 aCurrentMinute)
{
	Super::UpdateMinute(aCurrentMinute);
}

void UMS_CustomerSupervisor::UpdateScheduleEvent(int32 aScheduleEvent)
{
	Super::UpdateScheduleEvent(aScheduleEvent);

	// OpenMarket ~ DeadLine 8시에 고객 소환
	if(EMS_MarketScheduleEvent::CustomerStart == static_cast<EMS_MarketScheduleEvent>(aScheduleEvent))
	{
		StartCustomerSpawn();
	}
	else if(static_cast<EMS_MarketScheduleEvent>(aScheduleEvent) >= EMS_MarketScheduleEvent::Deadline)
	{
		StopCustomerSpawn();
	}
}

bool UMS_CustomerSupervisor::SpawnCustomer()
{
	FVector SpawnLocation = FVector::ZeroVector;
	FRotator SpawnRotator = FRotator::ZeroRotator;
	GetRandomSpawnPoint(SpawnLocation, SpawnRotator);
	
	TWeakObjectPtr<UMS_UnitBase> Unit = gUnitMng.CreateUnit(EMS_UnitType::CustomerAI, 0,true, SpawnLocation, SpawnRotator);
	if (UMS_CustomerAIUnit* CustomerAIUnit = Cast<UMS_CustomerAIUnit>(Unit))
	{
		CustomerAIUnit->RegisterCustomerAction(EMS_CustomerActionType::GoToMarket);
		CustomerAIUnits.Emplace(CustomerAIUnit);
		
		return true;
	}

	return false;
}

bool UMS_CustomerSupervisor::DestroyCustomer(UMS_CustomerAIUnit* aDestroyAIUnit)
{
	if(CustomerAIUnits.Contains(aDestroyAIUnit))
	{
		CustomerAIUnits.Remove(aDestroyAIUnit);
		gUnitMng.DestroyUnit(aDestroyAIUnit);
		return true;
	}

	return false;
}

void UMS_CustomerSupervisor::StartCustomerSpawn()
{
	SpawnIntervalDelayTime = 0.f;
	bStartCustomerSpawn = true;
	SpawnCustomer();
}

void UMS_CustomerSupervisor::StopCustomerSpawn()
{
	bStartCustomerSpawn = false;
}

void UMS_CustomerSupervisor::GetRandomSpawnPoint(FVector& SpawnLocation, FRotator& SpawnRotator)
{
	if(CustomerSpawnPoints.Num() < 1)
	{
		MS_ENSURE(false);
		MS_LOG_VERBOSITY(Error, TEXT("[%s] Has No CustomerSpawnPoints. Please Check \'Customer Spawn Point\' In Market Level."), *MS_FUNC_STRING);
		return;
	}

	const int32 SpawnPointIndex = FMath::RandRange(0, CustomerSpawnPoints.Num() - 1);
	if(CustomerSpawnPoints.IsValidIndex(SpawnPointIndex))
	{
		SpawnLocation = CustomerSpawnPoints[SpawnPointIndex]->GetSpawnLocation();
		SpawnRotator = CustomerSpawnPoints[SpawnPointIndex]->GetSpawnRotation();
	}
}

void UMS_CustomerSupervisor::InitCustomerSpawnPoint()
{
	CustomerSpawnPoints.Empty();
	TArray<AActor*> SpawnPoints;
	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMS_CustomerSpawnPoint::StaticClass(), SpawnPoints);

	for(const auto& SpawnPoint : SpawnPoints)
	{
		if(AMS_CustomerSpawnPoint* CustomerSpawnPoint = Cast<AMS_CustomerSpawnPoint>(SpawnPoint))
		{
			CustomerSpawnPoints.Emplace(CustomerSpawnPoint);
		}		
	}
}

void UMS_CustomerSupervisor::CashingDuckSplineActors() const
{
	TArray<AActor*> SplineActors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMS_CustomerSplineActor::StaticClass(), SplineActors);
	
	for (AActor* Spline : SplineActors)
	{
		AMS_CustomerSplineActor* SplineActor = Cast<AMS_CustomerSplineActor>(Spline);
		if(!SplineActor)
		{
			MS_LOG_VERBOSITY(Error, TEXT("Error Spline Actor Casting. Check AMS_DuckSplineActor"));
			return;
		}
		TObjectPtr<UMS_SplineUnit> SplineUnit = Cast<UMS_SplineUnit>(gUnitMng.CreateUnit(EMS_UnitType::CustomerSpline, INDEX_NONE, false));
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
