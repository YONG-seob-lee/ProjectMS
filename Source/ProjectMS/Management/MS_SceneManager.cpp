// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_SceneManager.h"

#include "CoreClass/Controller/MS_PlayerController.h"
#include "Data/Table/Caches/MS_LevelCacheTable.h"
#include "Kismet/GameplayStatics.h"
#include "MS_WidgetManager.h"
#include "Utility/MS_Define.h"
#include "Utility/Command/SceneCommand/MS_SceneCommand.h"
#include "Widget/MS_RootWidget.h"

AMS_SceneManager::AMS_SceneManager()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneManager = this;
}

void AMS_SceneManager::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	PersistentLevelWorld = GetWorld();

	const TObjectPtr<UWorld> World = GetWorld();
	MS_CHECK(World);

	const TObjectPtr<AMS_PlayerController> PlayerController = Cast<AMS_PlayerController>(World->GetFirstPlayerController());
	MS_CHECK(PlayerController);
	
	const TObjectPtr<UMS_TableManager> TableManager = PlayerController->GetTableManager();
	MS_CHECK(TableManager);

	LevelTable = Cast<UMS_LevelCacheTable>(TableManager->GetCacheTable(EMS_TableDataType::Level));
	MS_CHECK(LevelTable);

	const TObjectPtr<UMS_WidgetManager> WidgetManager = PlayerController->GetWidgetManager();
	RootWidget = WidgetManager->GetRootWidget();
}

void AMS_SceneManager::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AMS_SceneManager::RequestChangeScene(const TObjectPtr<UMS_SceneCommand>& aCommand)
{
	MS_CHECK(aCommand);
	NewCommand = aCommand;
	
	// Start Fade Out
	LevelChangeStep = EMS_FadeStep::EnterFadeOut;
	StartFade();
}

void AMS_SceneManager::StartFade()
{
	MS_CHECK(NewCommand);

	const EMS_TransitionStyle TransitionStyle = LevelChangeStep < EMS_FadeStep::Loading ? NewCommand->GetFadeOutTransitionStyle() : NewCommand->GetFadeInTransitionStyle();

	if(TransitionStyle == EMS_TransitionStyle::Undefined)
	{
		EndFade();
		return;
	}
	
	RootWidget->SetContentWidgetRender(LevelChangeStep < EMS_FadeStep::Loading ? NewCommand->GetFadeOutTransitionStyle() : NewCommand->GetFadeInTransitionStyle());
	
	GetWorld()->GetTimerManager().SetTimer(FadeTimerHandle, this, &AMS_SceneManager::ProcessFade, 0.01f, true);
}

void AMS_SceneManager::ProcessFade()
{
	FadeProgressRate += 0.01f;

	const EMS_FadeAnimationCurveType FadeAnimationCurveType = NewCommand->GetFadeAnimationCurveType();

	RootWidget->SetContentWidgetTransition(LevelChangeStep < EMS_FadeStep::Loading ? NewCommand->GetFadeOutTransitionStyle() : NewCommand->GetFadeInTransitionStyle(), FadeAnimationCurveType, FadeProgressRate);
		
	if (FadeProgressRate > 1.f)
	{
		FadeProgressRate = 1.f;
	}
	
	if (FadeProgressRate == 1.f)
	{
		EndFade();
	}
}

void AMS_SceneManager::EndFade()
{
	LevelChangeStep = LevelChangeStep < EMS_FadeStep::Loading ? EMS_FadeStep::ExitFadeOut : EMS_FadeStep::ExitFadeIn;
	GetWorld()->GetTimerManager().ClearTimer(FadeTimerHandle);
	
	FadeProgressRate = 0.f;
	
	if(NewCommand->GetLevelType() == EMS_LevelType::None)
	{
		// 위젯 변경만
		const TObjectPtr<UWorld> World = Cast<UWorld>(GetWorld());
		MS_CHECK(World);

		const TObjectPtr<AMS_PlayerController> PlayerController = Cast<AMS_PlayerController>(World->GetFirstPlayerController());
		MS_CHECK(PlayerController);
		
		const TObjectPtr<UMS_WidgetManager> WidgetManager = PlayerController->GetWidgetManager();
		MS_CHECK(WidgetManager);
	
		WidgetManager->RefreshContentWidget();
		WidgetManager->Create_Widget(NewCommand->GetNextWidgetName());
	}
	else
	{
		if(LevelChangeStep == EMS_FadeStep::ExitFadeOut)
		{
			// 레벨 이동
			RequestLevel();	
		}
		else if(LevelChangeStep == EMS_FadeStep::ExitFadeIn)
		{
			RootWidget->ActivatePreventionCover(false);
			RootWidget->ResetCanvasZOrder();
			LevelChangeStep = EMS_FadeStep::Finished;
		}
	}
}

void AMS_SceneManager::RequestLevel()
{
	MS_CHECK(NewCommand);

	if(LevelTable)
	{
		const FName LevelName = LevelTable->GetLevelName(NewCommand->GetPreviousLevelType());
		HandleUnloadLevel(LevelName);
	}
}

void AMS_SceneManager::HandleUnloadLevel(const FName& aLevelName)
{
	LevelChangeStep = EMS_FadeStep::Loading;
	FLatentActionInfo LatentActionInfo = {};
	LatentActionInfo.CallbackTarget = this;
	LatentActionInfo.ExecutionFunction = FName(TEXT("HandleLoadLevel"));
	LatentActionInfo.UUID = LatentActionInfoUUIDCounter++;
	LatentActionInfo.Linkage = 0;
	UGameplayStatics::UnloadStreamLevel(PersistentLevelWorld, aLevelName, LatentActionInfo, false);
}

void AMS_SceneManager::HandleLevelInstanceLoading()
{
}

void AMS_SceneManager::HandleLevelInstanceUnLoading()
{
}

void AMS_SceneManager::HandleLoadLevel()
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

void AMS_SceneManager::HandleLoadingLevel()
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

	const TObjectPtr<UWorld> World = Cast<UWorld>(GetWorld());
	MS_CHECK(World);

	const TObjectPtr<AMS_PlayerController> PlayerController = Cast<AMS_PlayerController>(World->GetFirstPlayerController());
	MS_CHECK(PlayerController);
	
	const TObjectPtr<UMS_WidgetManager> WidgetManager = PlayerController->GetWidgetManager();
	MS_CHECK(WidgetManager);
	
	WidgetManager->RefreshContentWidget();
	WidgetManager->Create_Widget(LevelTable->GetPrimitiveWidgetName(NewCommand->GetLevelType()));
	
	// Fade In
	LevelChangeStep = EMS_FadeStep::EnterFadeIn;
	StartFade();
}

AMS_SceneManager* AMS_SceneManager::GetInstance()
{
	return SceneManager;
}
