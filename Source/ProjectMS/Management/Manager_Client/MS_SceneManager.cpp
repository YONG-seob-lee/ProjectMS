// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_SceneManager.h"

#include "MS_InputManager.h"
#include "MS_SoundManager.h"
#include "Manager_Both/MS_TableManager.h"
#include "CoreClass/Controller/MS_PlayerController.h"
#include "Data/Table/Caches/MS_LevelCacheTable.h"
#include "Kismet/GameplayStatics.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "Utility/MS_Define.h"
#include "Utility/Command/SceneCommand/MS_SceneCommand.h"
#include "Widget/MS_RootWidget.h"

namespace Fade
{
	constexpr float ProgressRate = 0.01f;
}

UMS_SceneManager::UMS_SceneManager()
{
	SceneManager = this;
}

void UMS_SceneManager::Initialize()
{
	Super::Initialize();
	
	PersistentLevelWorld = GetWorld();

	LevelTable = Cast<UMS_LevelCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::Level));
	MS_CHECK(LevelTable);
}

void UMS_SceneManager::PostInitialize()
{
	Super::PostInitialize();
}

void UMS_SceneManager::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void UMS_SceneManager::InitRootWidget()
{
	RootWidget = gWidgetMng.GetRootWidget();
}

FMS_Level* UMS_SceneManager::GetCurrentLevelData()
{
	MS_CHECK(NewCommand);
	
	if(LevelTable)
	{
		return LevelTable->GetLevelData(NewCommand->GetLevelType());
	}

	return nullptr;
}

ALevelScriptActor* UMS_SceneManager::GetCurrentLevelScriptActor() const
{
	if (IsValid(LevelStreamingInst))
	{
		return LevelStreamingInst->GetLevelScriptActor();
	}

	return nullptr;
}

void UMS_SceneManager::RequestChangeScene(const TObjectPtr<UMS_SceneCommand>& aCommand)
{
	MS_CHECK(aCommand);
	NewCommand = aCommand;

	// 예외체크용 함수
	RootWidget->ActivatePreventionCover(true);
	gInputMng.SetAllowInteractActor(false);
	
	// Start Fade Out
	LevelChangeStep = EMS_FadeStep::EnterFadeOut;
	StartFade();
}

void UMS_SceneManager::StartFade()
{
	MS_CHECK(NewCommand);

	const EMS_TransitionStyle TransitionStyle = LevelChangeStep < EMS_FadeStep::Loading ? NewCommand->GetFadeOutTransitionStyle() : NewCommand->GetFadeInTransitionStyle();

	if(TransitionStyle == EMS_TransitionStyle::Undefined)
	{
		EndFade();
		return;
	}
	
	if(LevelChangeStep < EMS_FadeStep::Loading)
	{
		RootWidget->SetContentWidgetRender(NewCommand->GetFadeOutTransitionStyle());
		const float DefaultVolume = gSoundMng.GetDefaultVolume(EMS_SoundClassType::Master);
		gSoundMng.AdjustSoundVolume(EMS_SoundClassType::Master, DefaultVolume * (1.f - FadeProgressRate));
	}
	else
	{
		RootWidget->SetContentWidgetRender(NewCommand->GetFadeInTransitionStyle());
		const float DefaultVolume = gSoundMng.GetDefaultVolume(EMS_SoundClassType::Master);
		gSoundMng.AdjustSoundVolume(EMS_SoundClassType::Master, DefaultVolume * FadeProgressRate);
	}
	
	
	GetWorld()->GetTimerManager().SetTimer(FadeTimerHandle, this, &UMS_SceneManager::ProcessFade, Fade::ProgressRate, true);
}

void UMS_SceneManager::ProcessFade()
{
	FadeProgressRate += Fade::ProgressRate;

	const EMS_FadeAnimationCurveType FadeAnimationCurveType = NewCommand->GetFadeAnimationCurveType();

	if(LevelChangeStep < EMS_FadeStep::Loading)
	{
		RootWidget->SetContentWidgetTransition(NewCommand->GetFadeOutTransitionStyle() , FadeAnimationCurveType, FadeProgressRate);
		const float DefaultVolume = gSoundMng.GetDefaultVolume(EMS_SoundClassType::Master);
		gSoundMng.AdjustSoundVolume(EMS_SoundClassType::Master, DefaultVolume * (1.f - FadeProgressRate));
		MS_LOG(TEXT("SoundVolume : %f"), gSoundMng.GetSoundVolume(EMS_SoundClassType::Master));
	}
	else
	{
		RootWidget->SetContentWidgetTransition(NewCommand->GetFadeInTransitionStyle(), FadeAnimationCurveType, FadeProgressRate);

		const float DefaultVolume = gSoundMng.GetDefaultVolume(EMS_SoundClassType::Master);
		gSoundMng.AdjustSoundVolume(EMS_SoundClassType::Master, DefaultVolume * FadeProgressRate);
		MS_LOG(TEXT("SoundVolume : %f"), gSoundMng.GetSoundVolume(EMS_SoundClassType::Master));
	}
		
	if (FadeProgressRate > 1.f)
	{
		FadeProgressRate = 1.f;
	}
	
	if (FadeProgressRate == 1.f)
	{
		EndFade();
	}
}

void UMS_SceneManager::EndFade()
{
	LevelChangeStep = LevelChangeStep < EMS_FadeStep::Loading ? EMS_FadeStep::ExitFadeOut : EMS_FadeStep::ExitFadeIn;
	GetWorld()->GetTimerManager().ClearTimer(FadeTimerHandle);
	
	FadeProgressRate = 0.f;
	
	if(NewCommand->GetLevelType() == EMS_LevelType::None)
	{
		// 위젯 변경만	
		gWidgetMng.RefreshContentWidget();
		RootWidget->ActivatePreventionCover(false);

		if(NewCommand->GetNextWidgetName() != FName(TEXT("None")))
		{
			gWidgetMng.Create_Widget(NewCommand->GetNextWidgetName());
		}

		RootWidget->SetGeneralWidget(NewCommand->GetLevelType());
		if(NewCommand->OnFadeEventDelegate.IsBound())
		{
			NewCommand->OnFadeEventDelegate.Broadcast();
			NewCommand->OnFadeEventDelegate.RemoveAll(this);
		}

		gInputMng.SetAllowInteractActor(NewCommand->IsAllowInteractActor());
	}
	else
	{
		if(LevelChangeStep == EMS_FadeStep::ExitFadeOut)
		{
			// 레벨 이동
			RequestLevel();

			if(NewCommand->OnFadeEventDelegate.IsBound())
			{
				NewCommand->OnFadeEventDelegate.Broadcast();
				NewCommand->OnFadeEventDelegate.RemoveAll(this);
			}
		}
		else if(LevelChangeStep == EMS_FadeStep::ExitFadeIn)
		{
			RootWidget->ResetCanvasZOrder();
			RootWidget->SetGeneralWidget(NewCommand->GetLevelType());

			if(OnFadeFinishedEventDelegate.IsBound())
			{
				OnFadeFinishedEventDelegate.Broadcast();
				OnFadeFinishedEventDelegate.RemoveAll(this);
			}
			
			gInputMng.SetAllowInteractActor(NewCommand->IsAllowInteractActor());
			
			LevelChangeStep = EMS_FadeStep::Finished;
			MS_DeleteObject(NewCommand);
			NewCommand = nullptr;

		}
	}
}

void UMS_SceneManager::RequestLevel()
{
	MS_CHECK(NewCommand);

	if(LevelTable)
	{
		const FName LevelName = LevelTable->GetLevelName(NewCommand->GetPreviousLevelType());
		HandleUnloadLevel(LevelName);
	}
}

void UMS_SceneManager::HandleUnloadLevel(const FName& aLevelName)
{
	LevelChangeStep = EMS_FadeStep::Loading;
	FLatentActionInfo LatentActionInfo = {};
	LatentActionInfo.CallbackTarget = this;
	LatentActionInfo.ExecutionFunction = FName(TEXT("HandleLoadLevel"));
	LatentActionInfo.UUID = LatentActionInfoUUIDCounter++;
	LatentActionInfo.Linkage = 0;
	UGameplayStatics::UnloadStreamLevel(PersistentLevelWorld, aLevelName, LatentActionInfo, false);
}

void UMS_SceneManager::HandleLevelInstanceLoading()
{
}

void UMS_SceneManager::HandleLevelInstanceUnLoading()
{
}

void UMS_SceneManager::HandleLoadLevel()
{
	MS_CHECK(LevelTable);

	const FName LevelName = LevelTable->GetLevelName(NewCommand->GetLevelType());

	// const TObjectPtr<ULevelStreaming> LevelStreaming = UGameplayStatics::GetStreamingLevel(PersistentLevelWorld, LevelName);
	// TArray<TSoftObjectPtr<UWorld>>& BaseLayerLevelArray = Cast<AMS_LevelScriptActorBase>(LevelStreaming->GetLevelScriptActor())->BaseLayerLevelArray;
	//
	// const int32 NeedLevelInstanceLoadingCount = BaseLayerLevelArray.Num();
	// for(int32 i = 0 ; i < NeedLevelInstanceLoadingCount; i++)
	// {
	// 	bool Result = false;
	// 	const TObjectPtr<ULevelStreamingDynamic> LevelStreamingDynamic = ULevelStreamingDynamic::LoadLevelInstance(LevelStreaming->GetLoadedLevel(), BaseLayerLevelArray[i].GetLongPackageName(), FVector::ZeroVector, FRotator::ZeroRotator, Result);
	// 	if(LevelStreamingDynamic && Result)
	// 	{
	// 		LevelStreamingDynamic->OnLevelLoaded.AddDynamic(this, &AMS_SceneManager::HandleLevelInstanceLoading);
	// 		LevelStreamingDynamic->OnLevelUnloaded.AddDynamic(this, &AMS_SceneManager::HandleLevelInstanceUnLoading);
	// 	}
	// }
	
	FLatentActionInfo LatentActionInfo = {};
	LatentActionInfo.CallbackTarget = this;
	LatentActionInfo.ExecutionFunction = FName(TEXT("HandleLoadingLevel"));
	LatentActionInfo.UUID = LatentActionInfoUUIDCounter++;
	LatentActionInfo.Linkage = 0;

	UGameplayStatics::LoadStreamLevel(PersistentLevelWorld, LevelName, true, false, LatentActionInfo);
}

void UMS_SceneManager::HandleLoadingLevel()
{
	MS_CHECK(NewCommand);
	
	if(LevelTable)
	{
		const FName LevelName = LevelTable->GetLevelName(NewCommand->GetLevelType());
		LevelStreamingInst = UGameplayStatics::GetStreamingLevel(PersistentLevelWorld, LevelName);
	}


	if(OnLevelLoadedDelegate.IsBound())
	{
		OnLevelLoadedDelegate.Broadcast();
	}
	
	gWidgetMng.RefreshContentWidget();
	if (!LevelTable->GetPrimitiveWidgetName(NewCommand->GetLevelType()).IsNone() && NewCommand->GetNextWidgetName() == TEXT("None"))
	{
		gWidgetMng.Create_Widget(LevelTable->GetPrimitiveWidgetName(NewCommand->GetLevelType()));
	}

	// Sound Im ( BGM )
	RootWidget->SetBGMAnimation(NewCommand->GetLevelType());
	
	// Fade In
	LevelChangeStep = EMS_FadeStep::EnterFadeIn;
	StartFade();
}

UMS_SceneManager* UMS_SceneManager::GetInstance()
{
	return SceneManager;
}
