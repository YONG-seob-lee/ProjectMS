// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_StaffSupervisor.h"

#include "Controller/MS_PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Manager_Both/MS_UnitManager.h"
#include "PlayerState/MS_PlayerState.h"
#include "Mode/ModeObject/Container/MS_IssueTicketContainer.h"
#include "SpawnPoint/MS_StaffDuckSpawnPoint.h"
#include "Units/MS_StaffAIUnit.h"


UMS_StaffSupervisor::UMS_StaffSupervisor()
	: bSpawnCharacter(false)
{
}

void UMS_StaffSupervisor::Initialize()
{
	Super::Initialize();
}

void UMS_StaffSupervisor::Finalize()
{
	Super::Finalize();
}

void UMS_StaffSupervisor::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
}

void UMS_StaffSupervisor::Begin()
{
	Super::Begin();

	const TObjectPtr<UWorld> World = GetWorld();
	if (!IsValid(World))
	{
		return;
	}

	const TObjectPtr<AMS_PlayerController> PlayerController = World->GetFirstPlayerController<AMS_PlayerController>();
	if (!IsValid(PlayerController))
	{
		return;
	}

	const TObjectPtr<AMS_PlayerState> PlayerState = PlayerController->GetPlayerState<AMS_PlayerState>();
	if (!IsValid(PlayerState))
	{
		return;
	}

	StaffDatas = PlayerState->GetStaffDatas();

	for (int32 i = 0 ; i < StaffDatas.Num(); ++i)
	{
		if (StaffDatas[i].StaffId == 1)
		{
			NeedToSpawnStaffDataIndexToSpawnMinute.Emplace(i, 0);
		}
		else
		{
			// ToDo
		}
	}
}

void UMS_StaffSupervisor::Exit()
{
	Super::Exit();
}

void UMS_StaffSupervisor::SetIssueTicketContainer(TWeakObjectPtr<UMS_IssueTicketContainer> aIssueTicketContainer)
{
	IssueTicketContainer = aIssueTicketContainer;
}

void UMS_StaffSupervisor::UpdateMinute(int32 aCurrentMinute)
{
	Super::UpdateMinute(aCurrentMinute);

	if (bSpawnCharacter)
	{
		RequestSpawnCharacters(aCurrentMinute);
	}
}

void UMS_StaffSupervisor::UpdateScheduleEvent(int32 aScheduleEvent)
{
	Super::UpdateScheduleEvent(aScheduleEvent);

	if (aScheduleEvent == static_cast<int32>(EMS_MarketScheduleEvent::Prepare))
	{
		bSpawnCharacter = true;
	}
}

void UMS_StaffSupervisor::RequestSpawnCharacters(int32 aCurrentMinute)
{
	for (auto& It : NeedToSpawnStaffDataIndexToSpawnMinute)
	{
		if (It.Value <= aCurrentMinute)
		{
			MS_ENSURE(StaffDatas.IsValidIndex(It.Key));
			
			if (SpawnCharacter(StaffDatas[It.Key]))
			{
				NeedToSpawnStaffDataIndexToSpawnMinute.Remove(It.Key);
				return;
			}
		}
	}
}

bool UMS_StaffSupervisor::SpawnCharacter(const FMS_StaffData& aStaffData)
{
	TArray<AActor*> DuckSpawnPoints;
	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMS_StaffDuckSpawnPoint::StaticClass(), DuckSpawnPoints);

	for(AActor* SpawnPoint : DuckSpawnPoints)
	{
		AMS_StaffDuckSpawnPoint* DuckSpawnPoint = Cast<AMS_StaffDuckSpawnPoint>(SpawnPoint);
		if(!DuckSpawnPoint)
		{
			continue;
		}

		UMS_UnitBase* Unit = gUnitMng.CreateUnit(EMS_UnitType::StaffAI, aStaffData.StaffId,true, DuckSpawnPoint->GetSpawnLocation(), DuckSpawnPoint->GetSpawnRotation());
		if (UMS_StaffAIUnit* StaffAIUnit = Cast<UMS_StaffAIUnit>(Unit))
		{
			StaffAIUnits.Emplace(StaffAIUnit);

			StaffAIUnit->RegisterPersonalAction(EMS_PersonalActionType::ChangeClothes);
			return true;
		}
		
		MS_ENSURE(false);
	}

	return false;
}