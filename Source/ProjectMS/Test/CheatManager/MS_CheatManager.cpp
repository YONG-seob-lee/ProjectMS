// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_CheatManager.h"

#include "Controller/MS_PlayerController.h"
#include "GameUserSettings/MS_GameUserSettings.h"
#include "LevelScriptActors/MS_MarketLevelScriptActor.h"
#include "LevelScriptActors/MS_StageLevelScriptActor.h"
#include "Manager_Both/MS_UnitManager.h"
#include "Manager_Client/MS_ItemManager.h"
#include "Manager_Client/MS_ModeManager.h"
#include "Manager_Client/MS_SceneManager.h"
#include "Manager_Client/MS_ScheduleManager.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "Mode/ModeObject/Supervisor/Staff/MS_StaffSupervisor.h"
#include "Mode/ModeState/MS_ModeState_RunMarket.h"
#include "PlayerState/MS_PlayerState.h"
#include "Table/Caches/MS_StaffCacheTable.h"
#include "Widget/Dialog/MS_DialogWidget.h"

#if WITH_EDITOR
void UMS_CheatManager::TestCheatManager(const FString aTestString)
{
	gWidgetMng.ShowMessageOnScreen(aTestString);
}

void UMS_CheatManager::AIComeInMarket(int32 UnitId)
{
	const TObjectPtr<UMS_StaffCacheTable> StaffTable = Cast<UMS_StaffCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::Staff));
	MS_ENSURE(StaffTable);

	FString StaffName = FString();
	StaffTable->GetStaffName(UnitId, StaffName);
	const FString Behavior = TEXT("\"") + StaffName + TEXT("\" 이(가) 마켓에 입장했습니다.");

	if(const TObjectPtr<AMS_MarketLevelScriptActor> MarketLevelScriptActor = Cast<AMS_MarketLevelScriptActor>(gSceneMng.GetCurrentLevelScriptActor()))
	{
		MarketLevelScriptActor->AddTestAIActorComeInMarket(UnitId);
	}
	
	const int32 CurrentMinute = gScheduleMng.GetMinute();
	gUnitMng.OnBehaviorDelegate.Broadcast(FMS_BehaviorParameter(UnitId, CurrentMinute, FText::FromString(Behavior)));

	const FString Chatting = TEXT("(마켓 문을 열며)아 오늘은 어떤걸 구매해볼까나아");
	gUnitMng.OnChattingDelegate.Broadcast(FMS_ChattingParameter(UnitId, true, CurrentMinute, FText::FromString(Chatting)));

	gWidgetMng.ShowToastMessage(Behavior);
}

void UMS_CheatManager::AIExitMarket(int32 UnitId)
{
	const TObjectPtr<UMS_StaffCacheTable> StaffTable = Cast<UMS_StaffCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::Staff));
	MS_ENSURE(StaffTable);

	FString StaffName = FString();
	StaffTable->GetStaffName(UnitId, StaffName);

	const int32 CurrentMinute = gScheduleMng.GetMinute();
	const FString Behavior = TEXT("\"") + StaffName + TEXT("\" 이(가) 마켓에 퇴장했습니다.");

	gUnitMng.OnBehaviorDelegate.Broadcast(FMS_BehaviorParameter(UnitId, CurrentMinute, FText::FromString(Behavior)));
	
	const FString Chatting = TEXT("(마켓 을 나가며) 헤헷 다음에 또 와야찡~!");
	gUnitMng.OnChattingDelegate.Broadcast(FMS_ChattingParameter(UnitId, false, CurrentMinute, FText::FromString(Behavior)));
	
	gWidgetMng.ShowToastMessage(Behavior);
}

void UMS_CheatManager::AIChatting(int32 UnitId, const FString& Chatting)
{
	if(const TObjectPtr<AMS_MarketLevelScriptActor> MarketLevelScriptActor = Cast<AMS_MarketLevelScriptActor>(gSceneMng.GetCurrentLevelScriptActor()))
	{
		if(MarketLevelScriptActor->IsUnitInMarket(UnitId) == false)
		{
			const TObjectPtr<UMS_StaffCacheTable> StaffTable = Cast<UMS_StaffCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::Staff));
			MS_ENSURE(StaffTable);

			FString StaffName = FString();
			StaffTable->GetStaffName(UnitId, StaffName);
			gWidgetMng.ShowToastMessage(TEXT("\"") + StaffName + TEXT("\"") + TEXT(" 해당 유닛은 마켓안에 없습니다."));
			return;
		}
	}
	gUnitMng.OnChattingDelegate.Broadcast(FMS_ChattingParameter(UnitId, gScheduleMng.GetMinute(), FText::FromString(Chatting)));
}

void UMS_CheatManager::AIBehavior(int32 UnitId, const FString& Behavior)
{
	if(const TObjectPtr<AMS_MarketLevelScriptActor> MarketLevelScriptActor = Cast<AMS_MarketLevelScriptActor>(gSceneMng.GetCurrentLevelScriptActor()))
	{
		if(MarketLevelScriptActor->IsUnitInMarket(UnitId) == false)
		{
			const TObjectPtr<UMS_StaffCacheTable> StaffTable = Cast<UMS_StaffCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::Staff));
			MS_ENSURE(StaffTable);

			FString StaffName = FString();
			StaffTable->GetStaffName(UnitId, StaffName);

			gWidgetMng.ShowToastMessage(TEXT("\"") + StaffName + TEXT("\"") + TEXT(" 해당 유닛은 마켓안에 없습니다."));
			return;
		}
	}
	gUnitMng.OnBehaviorDelegate.Broadcast(FMS_BehaviorParameter(UnitId, gScheduleMng.GetMinute(), FText::FromString(Behavior)));
}

void UMS_CheatManager::AIPurchase(int32 UnitId, int32 ItemId, int32 ItemCount)
{
	if(const TObjectPtr<AMS_MarketLevelScriptActor> MarketLevelScriptActor = Cast<AMS_MarketLevelScriptActor>(gSceneMng.GetCurrentLevelScriptActor()))
	{
		if(MarketLevelScriptActor->IsUnitInMarket(UnitId) == false)
		{
			const TObjectPtr<UMS_StaffCacheTable> StaffTable = Cast<UMS_StaffCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::Staff));
			MS_ENSURE(StaffTable);

			FString StaffName = FString();
			StaffTable->GetStaffName(UnitId, StaffName);
			gWidgetMng.ShowToastMessage(TEXT("\"") + StaffName + TEXT("\"") + TEXT(" 해당 유닛은 마켓안에 없습니다."));
			return;
		}
	}
	gUnitMng.OnPurchaseDelegate.Broadcast(FMS_PurchaseParameter(UnitId, ItemId, ItemCount));
}

void UMS_CheatManager::AddStaff(int32 aStaffId)
{
	if (UMS_ModeState_RunMarket* RunMarket = Cast<UMS_ModeState_RunMarket>(gModeMng.GetCurrentModeState()))
	{
		if (UMS_StaffSupervisor* StaffSupervisor = RunMarket->GetStaffSupervisor())
		{
			StaffSupervisor->RequestSpawnCharacterInMarket(aStaffId);
		}
	}
}

void UMS_CheatManager::RemoveAllStaff()
{
	if (UMS_ModeState_RunMarket* RunMarket = Cast<UMS_ModeState_RunMarket>(gModeMng.GetCurrentModeState()))
	{
		if (UMS_StaffSupervisor* StaffSupervisor = RunMarket->GetStaffSupervisor())
		{
			StaffSupervisor->RemoveAllCharacter();
		}
	}
}

void UMS_CheatManager::DayNight(bool bTurnNight, bool bDirectly /* = true */)
{
	if(bTurnNight == true && bDirectly == false)
	{
		return;
	}
	
	if(const TObjectPtr<AMS_StageLevelScriptActor> TownLevelScriptActor = Cast<AMS_StageLevelScriptActor>(gSceneMng.GetCurrentLevelScriptActor()))
	{
		TownLevelScriptActor->SetDayAndNight(bTurnNight ? EMS_DayAndNight::Night : EMS_DayAndNight::Day, bDirectly);
	}
}

void UMS_CheatManager::RequestDialog(FString DialogType, float TypeSpeed)
{
	TArray<FMS_DialogParameter> DialogParameters;
	DialogParameters.Emplace(FMS_DialogParameter(DialogType, TypeSpeed));
	DialogParameters.Emplace(FMS_DialogParameter(DialogType, TypeSpeed));
	DialogParameters.Emplace(FMS_DialogParameter(DialogType, TypeSpeed));
	DialogParameters.Emplace(FMS_DialogParameter(DialogType, TypeSpeed));
	gWidgetMng.RequestDialog(DialogParameters);
}

void UMS_CheatManager::ResetProcessTutorial()
{
	const TObjectPtr<UMS_GameUserSettings> GameUserSettings = Cast<UMS_GameUserSettings>(GEngine->GetGameUserSettings());
	if(!GameUserSettings)
	{
		return;
	}

	GameUserSettings->ResetProcessTutorial();
}

void UMS_CheatManager::FastRun(int32 aMultiply)
{
	gScheduleMng.SetMultiplyIntervalSecondReal(aMultiply);
}

void UMS_CheatManager::Money(int32 aCount)
{
	const TObjectPtr<UWorld> World = GetWorld();
	MS_CHECK(World);

	const TObjectPtr<AMS_PlayerController> PlayerController = World->GetFirstPlayerController<AMS_PlayerController>();
	MS_CHECK(PlayerController);
	
	AMS_PlayerState* PlayerState = PlayerController->GetPlayerState<AMS_PlayerState>();
	MS_CHECK(PlayerState);

	PlayerState->SettleMoney(aCount);
	gItemMng.OnUpdateEarnMoneyDelegate.Broadcast(false);
}

void UMS_CheatManager::PictureMode(bool bPicture)
{
	gWidgetMng.GetRootWidget()->SetVisibility(bPicture ? ESlateVisibility::Collapsed : ESlateVisibility::SelfHitTestInvisible);
}
#endif
