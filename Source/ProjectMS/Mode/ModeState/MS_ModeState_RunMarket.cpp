// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ModeState_RunMarket.h"

#include "MS_ConstructibleLevelScriptActorBase.h"
#include "MS_Define.h"
#include "Character/AICharacter/StaffAICharacter/MS_StaffAICharacter.h"
#include "Controller/MS_PlayerController.h"
#include "Mode/ModeObject/Supervisor/Customer/MS_CustomerSupervisor.h"
#include "Mode/ModeObject/Supervisor/Staff/MS_StaffSupervisor.h"
#include "Manager_Client/MS_ModeManager.h"
#include "Manager_Client/MS_SceneManager.h"
#include "Manager_Client/MS_ScheduleManager.h"
#include "Manager_Client/MS_SequenceManager.h"
#include "Mode/ModeObject/Container/MS_IssueTicketContainer.h"
#include "Mode/ModeObject/Navigation/MS_GridBFS_2x2.h"
#include "PlayerState/MS_PlayerState.h"
#include "Units/MS_GateUnit.h"


UMS_ModeState_RunMarket::UMS_ModeState_RunMarket()
{
}

void UMS_ModeState_RunMarket::Initialize(uint8 aIndex, const FName& aName)
{
	Super::Initialize(aIndex, aName);

	ScheduleEvent.Empty();

	IssueTicketContainer = MS_NewObject<UMS_IssueTicketContainer>(this);
	if (IsValid(IssueTicketContainer))
	{
		IssueTicketContainer->Initialize();
	}
	
	StaffSupervisor = MS_NewObject<UMS_StaffSupervisor>(this);
	if (IsValid(StaffSupervisor))
	{
		StaffSupervisor->Initialize();
		StaffSupervisor->SetIssueTicketContainer(IssueTicketContainer);
	}
	
	CustomerSupervisor = MS_NewObject<UMS_CustomerSupervisor>(this);
	if (IsValid(CustomerSupervisor))
	{
		CustomerSupervisor->Initialize();
	}

	GridBFS_2x2 = MS_NewObject<UMS_GridBFS_2x2>(this);
}

void UMS_ModeState_RunMarket::Finalize()
{
	if (IsValid(CustomerSupervisor))
	{
		CustomerSupervisor->Finalize();
		MS_DeleteObject(CustomerSupervisor);
	}

	if (IsValid(StaffSupervisor))
	{
		StaffSupervisor->Finalize();
		MS_DeleteObject(StaffSupervisor);
	}

	if (IsValid(IssueTicketContainer))
	{
		IssueTicketContainer->Finalize();
		MS_DeleteObject(IssueTicketContainer);
	}
	
	Super::Finalize();
}

void UMS_ModeState_RunMarket::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);

	if (IsValid(StaffSupervisor))
	{
		StaffSupervisor->Tick(aDeltaTime);
	}
	
	if (IsValid(CustomerSupervisor))
	{
		CustomerSupervisor->Tick(aDeltaTime);
	}
}

void UMS_ModeState_RunMarket::Begin()
{
	Super::Begin();

	gScheduleMng.SetDailyTimeZone(EMS_DailyTimeZone::DayTimeWork);
	gScheduleMng.OnUpdateMinuteDelegate.AddUObject(this, &UMS_ModeState_RunMarket::UpdateMinute);
	gScheduleMng.OnUpdateScheduleEventDelegate.AddUObject(this, &UMS_ModeState_RunMarket::UpdateScheduleEvent);
	gScheduleMng.OnEndSchedule.AddUObject(this, &UMS_ModeState_RunMarket::EndSchedule);
	
	if (IsValid(StaffSupervisor))
	{
		StaffSupervisor->Begin();
	}
	
	if (IsValid(CustomerSupervisor))
	{
		CustomerSupervisor->Begin();
	}

	if (IsValid(GridBFS_2x2))
	{
		GridBFS_2x2->CollectAllZoneTypeMovingPoints();
	}
}

void UMS_ModeState_RunMarket::Exit()
{
	if (IsValid(CustomerSupervisor))
	{
		CustomerSupervisor->Finalize();
	}

	if (IsValid(StaffSupervisor))
	{
		StaffSupervisor->Finalize();
	}

	Super::Exit();
}

void UMS_ModeState_RunMarket::OnInputPointerDoubleClickEvent(FVector2D aPosition, const FHitResult& aInteractableHitResult)
{
	Super::OnInputPointerDoubleClickEvent(aPosition, aInteractableHitResult);

	if (const TObjectPtr<AActor> InteractActor = aInteractableHitResult.GetActor())
	{
		if(const TObjectPtr<AMS_StaffAICharacter> StaffDuck = Cast<AMS_StaffAICharacter>(InteractActor))
		{
			StaffDuck->ShowStaffStatusWidget(aPosition);
		}
	}
}

void UMS_ModeState_RunMarket::EndSchedule()
{
	// ToDo : Save Daily Data
	
	gScheduleMng.SetDailyTimeZone(EMS_DailyTimeZone::Evening);
	gModeMng.ChangeState(EMS_ModeState::Normal);
}

void UMS_ModeState_RunMarket::UpdateMinute(int32 aCurrentMinute)
{
	if (IsValid(StaffSupervisor))
	{
		StaffSupervisor->UpdateMinute(aCurrentMinute);
	}
	
	if (IsValid(CustomerSupervisor))
	{
		CustomerSupervisor->UpdateMinute(aCurrentMinute);
	}
}

void UMS_ModeState_RunMarket::UpdateScheduleEvent(int32 aScheduleEvent)
{
	if (IsValid(StaffSupervisor))
	{
		StaffSupervisor->UpdateScheduleEvent(aScheduleEvent);
	}
	
	if (IsValid(CustomerSupervisor))
	{
		CustomerSupervisor->UpdateScheduleEvent(aScheduleEvent);
	}

	if(static_cast<EMS_MarketScheduleEvent>(aScheduleEvent) == EMS_MarketScheduleEvent::TruckIn)
	{
		gScheduleMng.PauseSchedule();
		
		FMS_SequencePlayParameter Parameter;
		Parameter.OnFinishedSequenceCallback = [this]()
		{
			gScheduleMng.ResumeSchedule(38);
			const UWorld* World = GetWorld();
			if (!IsValid(World))
			{
				return;
			}

			const AMS_PlayerController* PlayerController = World->GetFirstPlayerController<AMS_PlayerController>();
			if (!IsValid(PlayerController))
			{
				return;
			}
	
			AMS_PlayerState* PlayerState = PlayerController->GetPlayerState<AMS_PlayerState>();
			if (!IsValid(PlayerState))
			{
				return;
			}
			PlayerState->OrganizeItems();
		};
		gSequenceMng.PlaySequence(EMS_SequenceType::Truck, Parameter);
	}
}

void UMS_ModeState_RunMarket::SearchPathToTarget(TArray<FIntVector2>& aOutPath, const FIntVector2& aStartPosition,
	const TArray<FIntVector2>& aTargetPositions) const
{
	aOutPath.Empty();
	
	if (AMS_ConstructibleLevelScriptActorBase* LevelScriptActor = Cast<AMS_ConstructibleLevelScriptActorBase>(gSceneMng.GetCurrentLevelScriptActor()))
	{
		if (!aTargetPositions.IsValidIndex(0))
		{
			MS_ENSURE(false);
			return;
		}

		// ZoneType
		EMS_ZoneType StartZoneType = LevelScriptActor->GetGridZoneType(aStartPosition);
		if (StartZoneType == EMS_ZoneType::None || StartZoneType == EMS_ZoneType::Passage)
		{
			// MS_ENSURE(false);
			return;
		}
		
		EMS_ZoneType TargetZoneType = LevelScriptActor->GetGridZoneType(aTargetPositions[0]);
		if (StartZoneType == EMS_ZoneType::None || StartZoneType == EMS_ZoneType::Passage)
		{
			MS_ENSURE(false);
			return;
		}

		// Search
		if (StartZoneType == TargetZoneType)
		{
			GridBFS_2x2->Search(aOutPath, StartZoneType, aStartPosition, aTargetPositions);
		}
		else
		{
			// Start에서 Gate까지
			TArray<FIntVector2> PathToGate;
			
			TArray<TWeakObjectPtr<UMS_GateUnit>> GatesUnits;
			LevelScriptActor->GetGateUnitsInLevel(GatesUnits, StartZoneType, TargetZoneType);

			TArray<FIntVector2> GatePositions = {};
			for (TWeakObjectPtr<UMS_GateUnit> GateUnit : GatesUnits)
			{
				if (GateUnit != nullptr)
				{
					GatePositions.Emplace(GateUnit->GetGridPosition());
				}
			}
			
			GridBFS_2x2->Search(PathToGate, StartZoneType, aStartPosition, GatePositions);

			
			// Linked Gate에서 타겟까지
			if (PathToGate.Num() != 0)
			{
				TArray<FIntVector2> PathToTarget;
			
				TWeakObjectPtr<UMS_GateUnit> TargetGateUnit;
				for (TWeakObjectPtr<UMS_GateUnit> GateUnit : GatesUnits)
				{
					if (GateUnit != nullptr)
					{
						if (GateUnit->GetGridPosition() == PathToGate.Last())
						{
							TargetGateUnit = GateUnit;
						}
					}
				}

				GridBFS_2x2->Search(PathToTarget, TargetGateUnit->GetLinkedZoneType(), TargetGateUnit->GetLinkedGridPosition(), aTargetPositions);

				if (PathToTarget.Num() != 0)
				{
					aOutPath.Append(PathToGate);
					aOutPath.Append(PathToTarget);
				}
				else
				{
					// ToDo : 다른 Gate를 통하면 목표에 갈 수 있나
				}
			}
		}
	}
}
