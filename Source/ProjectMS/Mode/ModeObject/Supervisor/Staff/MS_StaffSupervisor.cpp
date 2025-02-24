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

	PlayerStaffDatas = PlayerState->GetStaffDatas();

	InitStaffSpawnPoint();
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
	for (const auto& StaffSpawnPoint : StaffSpawnPoints)
	{
		TArray<FMS_PlayerStaffData*> SpawnPlayerStaffDatas = {};
		
		if(StaffSpawnPoint->IsSpawnThisMinute(aCurrentMinute, SpawnPlayerStaffDatas))
		{
			for(FMS_PlayerStaffData* PlayerStaffData : SpawnPlayerStaffDatas)
			{
				SpawnCharacter(PlayerStaffData, StaffSpawnPoint->GetSpawnLocation(), StaffSpawnPoint->GetSpawnRotation());
			}
		}
	}
}

#if WITH_EDITOR
void UMS_StaffSupervisor::RequestSpawnCharacterInMarket(int32 aStaffId)
{
	SpawnCharacter(aStaffId, FVector(500.f, 500.f, 80.f), FRotator(0.f,0.f,0.f));
}
#endif

bool UMS_StaffSupervisor::SpawnCharacter(int32 aStaffId, const FVector& SpawnLocation, const FRotator& SpawnRotator)
{
	UMS_UnitBase* Unit = gUnitMng.CreateUnit(EMS_UnitType::StaffAI, aStaffId,true, SpawnLocation, SpawnRotator);
	if (UMS_StaffAIUnit* StaffAIUnit = Cast<UMS_StaffAIUnit>(Unit))
	{
		StaffAIUnits.Emplace(StaffAIUnit);
		
		return true;
	}
		
	MS_ENSURE(false);
	return false;
}

bool UMS_StaffSupervisor::SpawnCharacter(FMS_PlayerStaffData* aPlayerStaffData, const FVector& SpawnLocation, const FRotator& SpawnRotator)
{
	UMS_UnitBase* Unit = gUnitMng.CreateUnit(EMS_UnitType::StaffAI, aPlayerStaffData->StaffId,true, SpawnLocation, SpawnRotator);
	if (UMS_StaffAIUnit* StaffAIUnit = Cast<UMS_StaffAIUnit>(Unit))
	{
		StaffAIUnits.Emplace(StaffAIUnit);
		StaffAIUnit->SetPlayerStaffData(*aPlayerStaffData);
		
		return true;
	}
		
	MS_ENSURE(false);
	return false;
}

void UMS_StaffSupervisor::RemoveAllCharacter()
{
	gUnitMng.DestroyAllUnits(EMS_UnitType::StaffAI);
	StaffAIUnits.Empty();
}

void UMS_StaffSupervisor::RegisterPreSpawnedCharacter(int32 aStaffId, TWeakObjectPtr<AMS_CharacterBase> aCharacter)
{
	if (aCharacter == nullptr)
	{
		return;
	}
	
	TObjectPtr<UMS_StaffAIUnit> StaffUnit = Cast<UMS_StaffAIUnit>(gUnitMng.CreateUnit(EMS_UnitType::StaffAI, aStaffId, false));
	if (IsValid(StaffUnit))
	{
		if (!StaffUnit->SetUnitCharacter(aCharacter.Get()))
		{
			MS_ERROR(TEXT("[%s] Set Unit Character Fail"), *MS_FUNC_STRING);
			MS_ENSURE(false);
		}
		else
		{
			StaffAIUnits.Emplace(StaffUnit);

			bool bFlag = false;
			for (const auto& PlayerStaffData : PlayerStaffDatas)
			{
				if (PlayerStaffData.StaffId == aStaffId)
				{
					StaffUnit->SetPlayerStaffData(PlayerStaffData);
					bFlag = true;
					break;
				}
			}
			if (bFlag == false)
			{
				StaffUnit->SetPlayerStaffData(FMS_PlayerStaffData(aStaffId));
				MS_ERROR(TEXT("[%s] No Prespawned Character's Player Staff Data"), *MS_FUNC_STRING);
				MS_ERROR(TEXT("[%s] 세이브 데이터를 지워!!!!!"), *MS_FUNC_STRING);
				MS_ENSURE(false);
			}

		}
	}
	else
	{
		MS_ERROR(TEXT("[%s] Create Unit Fail"), *MS_FUNC_STRING);
		MS_ENSURE(false);
	}
}

void UMS_StaffSupervisor::InitStaffSpawnPoint()
{
	StaffSpawnPoints.Empty();
	TArray<AActor*> SpawnPoints;
	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMS_StaffDuckSpawnPoint::StaticClass(), SpawnPoints);

	for(const auto& SpawnPoint : SpawnPoints)
	{
		if(AMS_StaffDuckSpawnPoint* StaffSpawnPoint = Cast<AMS_StaffDuckSpawnPoint>(SpawnPoint))
		{
			StaffSpawnPoints.Emplace(StaffSpawnPoint);
		}		
	}	
	
	for(auto& StaffData : PlayerStaffDatas)
	{
		const int32 TargetSpawnIndex = FMath::RandRange(0, StaffSpawnPoints.Num() - 1);
		
		if(StaffSpawnPoints.IsValidIndex(TargetSpawnIndex))
		{
			StaffSpawnPoints[TargetSpawnIndex]->UpdateSpawnData(&StaffData, FMath::RandRange(0, 30));
		}
	}
}
