﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_StageLevelScriptActor.h"

#include "MS_ActorBase.h"
#include "Kismet/GameplayStatics.h"
#include "Manager_Both/MS_UnitManager.h"
#include "Manager_Client/MS_InputManager.h"
#include "SpawnPoint/MS_OutsideDuckSpawnPoint.h"
#include "Units/MS_SplineUnit.h"
#include "Components/LightComponent.h"
#include "Engine/DirectionalLight.h"
#include "Manager_Client/MS_HISMManager.h"
#include "Manager_Client/MS_ScheduleManager.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "Prop/NightProp/MS_NightProp.h"
#include "Prop/Spline/MS_DuckSplineActor.h"
#include "Prop/Spline/MS_VehicleSplineActor.h"
#include "Vehicle/MS_VehicleCharacter.h"


// Sets default values
AMS_StageLevelScriptActor::AMS_StageLevelScriptActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AMS_StageLevelScriptActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	CashingDirectionalLight();
	CashingNightPropActors();
	CashingNightCarActors();
	
	CashingCarSplineActors();
	CashingDuckSplineActors();

	CollectOutsideDuckSpawnPoint();
}

// Called when the game starts or when spawned
void AMS_StageLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();
	
	gInputMng.OnPointerDownDelegate.AddDynamic(this, &AMS_StageLevelScriptActor::OnPressDownEvent);
	gInputMng.OnPointerUpDelegate.AddDynamic(this, &AMS_StageLevelScriptActor::OnPressUpEvent);

	const FMS_GameDate& GameDate = gScheduleMng.GetGameDate();
	if(FMS_GameDate::IsNight(GameDate.DailyTimeZone))
	{
		SetDayAndNight(EMS_DayAndNight::Night, true);
	}
	else
	{
		SetDayAndNight(EMS_DayAndNight::Day, true);
	}
}

void AMS_StageLevelScriptActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	gInputMng.OnPointerDownDelegate.RemoveAll(this);
	gInputMng.OnPointerUpDelegate.RemoveAll(this);

	gHISMMng.ClearInstances();
	gUnitMng.DestroyAllUnits();
	
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void AMS_StageLevelScriptActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bStartNightToDayTrigger)
	{
		ProcessNightToDay(DeltaTime);
	}
}

void AMS_StageLevelScriptActor::SetDayAndNight(EMS_DayAndNight aDayAndNight, bool bDirectly /* = false */)
{
	SetDayAndNight_Internal(aDayAndNight, bDirectly);
}

void AMS_StageLevelScriptActor::SetDayAndNight_Internal(EMS_DayAndNight aDayAndNight, bool bDirectly)
{
	if(bDirectly)
	{
		SetLightColor(aDayAndNight);
		SetLightProp(aDayAndNight);
		SetLightCar(aDayAndNight);
	}
	else
	{
		gInputMng.SetAllowInteractActor(false);
		DirectionalLightColorVolume = 0.f;
		bStartNightToDayTrigger = true;
	}
}

void AMS_StageLevelScriptActor::SetLightColor(EMS_DayAndNight aDayAndNight) const
{
	if(DirectionalLight == nullptr)
	{
		return;
	}
	
	if(aDayAndNight == EMS_DayAndNight::Day)
	{
		DirectionalLight->GetLightComponent()->SetLightColor(FColor(255.f, 255.f, 255.f));
	}
	else
	{
		DirectionalLight->GetLightComponent()->SetLightColor(FColor(45.f, 45.f, 45.f));
	}
}

void AMS_StageLevelScriptActor::SetLightProp(EMS_DayAndNight aDayAndNight)
{
	if(aDayAndNight == EMS_DayAndNight::Day)
	{
		for(const auto& NightProp : NightProps)
		{
			if(NightProp->IsContainMesh())
			{
				NightProp->TurnOffLight();
			}
			else
			{
				NightProp->SetActorHiddenInGame(true);
			}
		}
	}
	else
	{
		for(const auto& NightProp : NightProps)
		{
			if(NightProp->IsContainMesh())
			{
				NightProp->TurnOnLight();
			}
			else
			{
				NightProp->SetActorHiddenInGame(false);
			}
		}
	}
}

void AMS_StageLevelScriptActor::SetLightCar(EMS_DayAndNight aDayAndNight)
{
	if(aDayAndNight == EMS_DayAndNight::Day)
	{
		for(const auto& Car : Cars)
		{
			Car->TurnOffLight();
		}
	}
	else
	{
		for(const auto& Car : Cars)
		{
			Car->TurnOnLight();
		}
	}
}

void AMS_StageLevelScriptActor::CollectOutsideDuckSpawnPoint() const
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
		
		gUnitMng.CreateUnit(EMS_UnitType::OutsideAI, 0,true, DuckSpawnPoint->GetSpawnLocation(), DuckSpawnPoint->GetSpawnRotation());
	}
}

void AMS_StageLevelScriptActor::CashingNightPropActors()
{
	TArray<AActor*> Props;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMS_NightProp::StaticClass(), Props);

	for(const auto& Prop : Props)
	{
		if(AMS_NightProp* NightProp = Cast<AMS_NightProp>(Prop))
		{
			NightProps.Emplace(NightProp);
		}
	}
}

void AMS_StageLevelScriptActor::CashingNightCarActors()
{
	TArray<AActor*> VehicleActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMS_VehicleCharacter::StaticClass(), VehicleActors);

	for(const auto& Vehicle : VehicleActors)
	{
		if(AMS_VehicleCharacter* Car = Cast<AMS_VehicleCharacter>(Vehicle))
		{
			Cars.Emplace(Car);
		}
	}
}

void AMS_StageLevelScriptActor::CashingCarSplineActors() const
{
	TArray<AActor*> SplineActors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMS_VehicleSplineActor::StaticClass(), SplineActors);
	
	for (AActor* Spline : SplineActors)
	{
		AMS_VehicleSplineActor* SplineActor = Cast<AMS_VehicleSplineActor>(Spline);
		if(!SplineActor)
		{
			MS_ERROR(TEXT("Error Spline Actor Casting. Check AMS_VehicleSplineActor"));
			return;
		}
		TObjectPtr<UMS_SplineUnit> SplineUnit = Cast<UMS_SplineUnit>(gUnitMng.CreateUnit(EMS_UnitType::CarSpline, INDEX_NONE, false));
		 if (IsValid(SplineUnit))
		 {
		 	// Set Unit Actor
		 	if (!SplineUnit->SetUnitActor(SplineActor))
		 	{
		 		MS_ERROR(TEXT("[%s] Set Unit Actor Fail"), *MS_FUNC_STRING);
		 		MS_ENSURE(false);
		 	}
		 }
		 else
		 {
		 	MS_ERROR(TEXT("[%s] Create Unit Fail"), *MS_FUNC_STRING);
		 	MS_ENSURE(false);
		 }
	}
}

void AMS_StageLevelScriptActor::CashingDuckSplineActors() const
{
	TArray<AActor*> SplineActors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMS_DuckSplineActor::StaticClass(), SplineActors);
	
	for (AActor* Spline : SplineActors)
	{
		AMS_DuckSplineActor* SplineActor = Cast<AMS_DuckSplineActor>(Spline);
		if(!SplineActor)
		{
			MS_ERROR(TEXT("Error Spline Actor Casting. Check AMS_DuckSplineActor"));
			return;
		}
		TObjectPtr<UMS_SplineUnit> SplineUnit = Cast<UMS_SplineUnit>(gUnitMng.CreateUnit(EMS_UnitType::DuckSpline, INDEX_NONE, false));
		if (IsValid(SplineUnit))
		{
			// Set Unit Actor
			if (!SplineUnit->SetUnitActor(SplineActor))
			{
				MS_ERROR(TEXT("[%s] Set Unit Actor Fail"), *MS_FUNC_STRING);
				MS_ENSURE(false);
			}
		}
		else
		{
			MS_ERROR(TEXT("[%s] Create Unit Fail"), *MS_FUNC_STRING);
			MS_ENSURE(false);
		}
	}
}

void AMS_StageLevelScriptActor::OnPressDownEvent(FVector2D aPointerDownPosition, const FHitResult& aInteractableHitResult)
{
	AActor* PointerDownActor = aInteractableHitResult.GetActor();
	if(IsValid(PointerDownActor))
	{
		if(const TObjectPtr<AMS_ActorBase> TargetActor = Cast<AMS_ActorBase>(PointerDownActor))
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
		if(const TObjectPtr<AMS_ActorBase> TargetActor = Cast<AMS_ActorBase>(PointerUpActor))
		{
			if(TargetActor->HasInteractionComponent())
			{
				TargetActor->OnPressUpEvent();
			}
		}
	}
}

void AMS_StageLevelScriptActor::ProcessNightToDay(float DeltaTime)
{
	MS_LOG(TEXT("DirectionalLightColorVolume = %f"), DirectionalLightColorVolume);
	DirectionalLightColorVolume += DeltaTime * 50.f;
	if(DirectionalLightColorVolume >= 255.f)
	{
		bStartNightToDayTrigger = false;
		gInputMng.SetAllowInteractActor(true);
		gWidgetMng.ShowToastMessage(TEXT("아침이 밝았습니다~~"));
	}
	else if(DirectionalLightColorVolume >= 200.f)
	{
		SetLightColor(EMS_DayAndNight::Day);
		SetLightProp(EMS_DayAndNight::Day);
		SetLightCar(EMS_DayAndNight::Day);
	}

	if(DirectionalLight)
	{
		DirectionalLight->GetLightComponent()->SetLightColor(FColor(DirectionalLightColorVolume, DirectionalLightColorVolume, DirectionalLightColorVolume));
	}
}
