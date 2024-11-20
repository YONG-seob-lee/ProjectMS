// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/MS_SceneManager.h"

#include "CoreClass/Controller/MS_PlayerController.h"
#include "Data/Table/Caches/MS_LevelCacheTable.h"
#include "Kismet/GameplayStatics.h"
#include "../Public/MS_WidgetManager.h"
#include "UI/Widget/MS_Widget.h"
#include "Utility/MS_Define.h"
#include "Utility/Command/SceneCommand/MS_SceneCommand.h"

void AMS_SceneManager::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	PersistentLevelWorld = GetWorld();

	const TObjectPtr<UWorld> World = GetWorld();
	MS_CHECK(World);

	const TObjectPtr<AMS_PlayerController> PlayerController = Cast<AMS_PlayerController>(World->GetFirstPlayerController());
	MS_CHECK(PlayerController);
	
	const TWeakObjectPtr<UMS_TableManager> TableManager = PlayerController->GetTableManager();
	MS_CHECK(TableManager.IsValid());

	LevelTable = Cast<UMS_LevelCacheTable>(TableManager->GetCacheTable(EMS_TableDataType::Level));
	MS_CHECK(LevelTable.IsValid());
}

void AMS_SceneManager::RequestChangeScene(const TObjectPtr<UMS_SceneCommand>& aCommand)
{
	MS_CHECK(LevelChangeStep == EMS_FadeStep::Undefined);
	
	MS_CHECK(aCommand);
	NewCommand = aCommand;

	const TObjectPtr<UWorld> World = Cast<UWorld>(GetWorld());
	MS_CHECK(World);

	const TObjectPtr<AMS_PlayerController> PlayerController = Cast<AMS_PlayerController>(World->GetFirstPlayerController());
	MS_CHECK(PlayerController);
	
	const TWeakObjectPtr<UMS_WidgetManager> WidgetManager = PlayerController->GetWidgetManager();
	MS_CHECK(WidgetManager.IsValid());

	const FName WidgetName = LevelTable->GetPrimitiveWidgetName(NewCommand->GetPreviousLevelType());
	
	FadeWidget = WidgetManager->GetWidget(WidgetName);
	// Fade Out
	StartFade(FadeWidget);
}

void AMS_SceneManager::LoadLevel(const FName& aLevelName)
{
	HandleLoadLevel(aLevelName);
}

void AMS_SceneManager::StartFade(const TObjectPtr<UMS_Widget>& aFadeWidget)
{
	MS_CHECK(NewCommand);
	LevelChangeStep = EMS_FadeStep::EnterFadeOut;

	switch(LevelChangeStep < EMS_FadeStep::Loading ? NewCommand->GetFadeOutTransitionStyle() : NewCommand->GetFadeInTransitionStyle())
	{
	case EMS_TransitionStyle::FadeFromLeavingPage :
		{
			aFadeWidget->SetRenderOpacity(1.f);
		}
	case EMS_TransitionStyle::FadeFromEnteringPage :
		{
			aFadeWidget->SetRenderOpacity(0.f);
		}
	case EMS_TransitionStyle::FloatFromTop :
		{
			aFadeWidget->SetRenderTranslation(FVector2D(0.f, -aFadeWidget->GetContentFrameSize().Y));
		}
	case EMS_TransitionStyle::FloatFromBottom :
		{
			aFadeWidget->SetRenderTranslation(FVector2D { 0.0f, aFadeWidget->GetContentFrameSize().Y });
		}
	case EMS_TransitionStyle::FloatFromLeft :
		{
			aFadeWidget->SetRenderTranslation(FVector2D { -aFadeWidget->GetContentFrameSize().X, 0.0f });
		}
	case EMS_TransitionStyle::FloatFromRight :
		{
			aFadeWidget->SetRenderTranslation(FVector2D { aFadeWidget->GetContentFrameSize().X, 0.0f });
		}
	default:
		{
			
		}
	}
	
	aFadeWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	//ActivatePreventionCover();

	GetWorld()->GetTimerManager().SetTimer(FadeTimerHandle, this, &AMS_SceneManager::ProcessFade, 0.01f, true);
}

void AMS_SceneManager::ProcessFade()
{
	FadeProgressRate += 0.01f;
	
	EMS_FadeAnimationCurveType FadeAnimationCurveType = NewCommand->GetFadeAnimationCurveType();
	
	switch(LevelChangeStep < EMS_FadeStep::Loading ? NewCommand->GetFadeOutTransitionStyle() : NewCommand->GetFadeInTransitionStyle())
	{
	case EMS_TransitionStyle::FadeFromLeavingPage :
		{
			FadeWidget->SetRenderOpacity(ConvertFadeAnimationCurveValue(1.0 - FadeProgressRate, FadeAnimationCurveType));
		}
	case EMS_TransitionStyle::FadeFromEnteringPage :
		{
			FadeWidget->SetRenderOpacity(ConvertFadeAnimationCurveValue(FadeProgressRate, FadeAnimationCurveType));
		}
	case EMS_TransitionStyle::FloatFromTop :
		{
			FadeWidget->SetRenderTranslation(FVector2D { 0.0f, ConvertFadeAnimationCurveValue(1.0 - FadeProgressRate, FadeAnimationCurveType) * -FadeWidget->GetContentFrameSize().Y });
		}
	case EMS_TransitionStyle::FloatFromBottom :
		{
			FadeWidget->SetRenderTranslation(FVector2D { 0.0f, ConvertFadeAnimationCurveValue(1.0 - FadeProgressRate, FadeAnimationCurveType) * FadeWidget->GetContentFrameSize().Y });
		}
	case EMS_TransitionStyle::FloatFromLeft :
		{
			FadeWidget->SetRenderTranslation(FVector2D { ConvertFadeAnimationCurveValue(1.0 - FadeProgressRate, FadeAnimationCurveType) * -FadeWidget->GetContentFrameSize().X, 0.0f });
		}
	case EMS_TransitionStyle::FloatFromRight :
		{
			FadeWidget->SetRenderTranslation(FVector2D { ConvertFadeAnimationCurveValue(1.0 - FadeProgressRate, FadeAnimationCurveType) * FadeWidget->GetContentFrameSize().X, 0.0f });
		}
	default:
		{
			
		}
	}
	
	if (FadeProgressRate > 1.0)
	{
		FadeProgressRate = 1.0;
	}
	
	if (FadeProgressRate == 1.0)
	{
		EndFade();
	}
}

void AMS_SceneManager::EndFade()
{
	LevelChangeStep = EMS_FadeStep::ExitFadeOut;
	GetWorld()->GetTimerManager().ClearTimer(FadeTimerHandle);
	
	FadeProgressRate = 0.f;

	if(NewCommand->GetLevelType() == EMS_LevelType::None)
	{
		// 위젯 변경만
	}
	else
	{
		// 레벨 이동
		RequestLevel();
	}
}

void AMS_SceneManager::RequestLevel()
{
	MS_CHECK(NewCommand);

	if(LevelTable.IsValid())
	{
		const FName LevelName = LevelTable->GetLevelName(NewCommand->GetLevelType());
		HandleUnloadLevel(LevelName);
	}
}

void AMS_SceneManager::HandleUnloadLevel(const FName& aLevelName)
{
	FLatentActionInfo LatentActionInfo = {};
	LatentActionInfo.CallbackTarget = this;
	LatentActionInfo.ExecutionFunction = FName(TEXT("HandleLoadLevel"));
	LatentActionInfo.UUID = LatentActionInfoUUIDCounter++;
	LatentActionInfo.Linkage = 0;
	UGameplayStatics::UnloadStreamLevel(PersistentLevelWorld, aLevelName, LatentActionInfo, false);
}

void AMS_SceneManager::HandleLoadLevel(const FName& aLevelName)
{
	FLatentActionInfo LatentActionInfo = {};
	LatentActionInfo.CallbackTarget = this;
	LatentActionInfo.ExecutionFunction = FName(TEXT("HandleLoadingLevel"));
	LatentActionInfo.UUID = LatentActionInfoUUIDCounter++;
	LatentActionInfo.Linkage = 0;
	
	UGameplayStatics::LoadStreamLevel(PersistentLevelWorld, aLevelName, true, false, LatentActionInfo);
}

void AMS_SceneManager::HandleLoadingLevel()
{
	MS_CHECK(NewCommand);
	MS_CHECK(LevelTable.IsValid());

	const FName LevelName = LevelTable->GetLevelName(NewCommand->GetLevelType());
	LevelStreamingInst = UGameplayStatics::GetStreamingLevel(PersistentLevelWorld, LevelName);

	if(OnLevelLoadedDelegate.IsBound())
	{
		OnLevelLoadedDelegate.Broadcast();
	}

	const TObjectPtr<UWorld> World = Cast<UWorld>(GetWorld());
	MS_CHECK(World);

	const TObjectPtr<AMS_PlayerController> PlayerController = Cast<AMS_PlayerController>(World->GetFirstPlayerController());
	MS_CHECK(PlayerController);
	
	const TWeakObjectPtr<UMS_WidgetManager> WidgetManager = PlayerController->GetWidgetManager();
	MS_CHECK(WidgetManager.IsValid());
	
	const TObjectPtr<UMS_Widget> Widget = WidgetManager->Create_Widget(LevelTable->GetPrimitiveWidgetName(NewCommand->GetLevelType()));
	// Fade In
	StartFade(Widget);
}

void AMS_SceneManager::HandleLevelLoad()
{
	MS_CHECK(NewCommand);
	MS_CHECK(LevelTable.IsValid());
	
	const FName LevelName = LevelTable->GetLevelName(NewCommand->GetLevelType());
	HandleLoadLevel(LevelName);
}