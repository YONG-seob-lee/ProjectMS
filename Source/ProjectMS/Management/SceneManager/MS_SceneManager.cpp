// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_SceneManager.h"

#include "CoreClass/Controller/MS_PlayerController.h"
#include "Components/CanvasPanelSlot.h"
#include "Data/Table/Caches/MS_LevelCacheTable.h"
#include "Kismet/GameplayStatics.h"
#include "Management/WidgetManager/MS_WidgetManager.h"
#include "UI/Widget/MS_Widget.h"
#include "Utility/MS_Define.h"
#include "Utility/Command/SceneCommand/MS_SceneCommand.h"

void AMS_SceneManager::PostInitializeComponents()
{
	PersistentLevelWorld = GetWorld();

	const TWeakObjectPtr<UMS_Management> Management = Cast<UMS_Management>(GetOuter());
	MS_CHECK(Management.IsValid());
	
	const TWeakObjectPtr<UMS_TableManager> TableManager = Management->GetTableManager();
	MS_CHECK(TableManager.IsValid());

	LevelTable = Cast<UMS_LevelCacheTable>(TableManager->GetCacheTable(EMS_TableDataType::Level));
	MS_CHECK(LevelTable.IsValid());
}

void AMS_SceneManager::RequestChangeScene(const TObjectPtr<UMS_SceneCommand>& aCommand)
{
	MS_CHECK(LevelChangeStep != EMS_FadeStep::Undefined);
	
	MS_CHECK(aCommand);
	NewCommand = aCommand;

	// Fade Out
	StartFade(true);
}

void AMS_SceneManager::StartFade(bool bStartFadeOut)
{
	MS_CHECK(NewCommand);
	LevelChangeStep = EMS_FadeStep::EnterFadeOut;

	const TWeakObjectPtr<UMS_Management> Management = Cast<UMS_Management>(GetOuter());
	MS_CHECK(Management.IsValid());

	const TWeakObjectPtr<UMS_WidgetManager> WidgetManager = Management->GetWidgetManager();
	MS_CHECK(WidgetManager.IsValid());
	
	LeavingWidget = WidgetManager->GetCurrentWidget();
	MS_CHECK(LeavingWidget);
	EnterWidget = MS_NewObject<UMS_Widget>(this, bStartFadeOut ? NewCommand->GetLoadingWidget() : NewCommand->GetNextWidget());
	MS_CHECK(EnterWidget);
	
	switch(NewCommand->GetTransitionStyle())
	{
	case EMS_TransitionStyle::FadeFromLeavingPage :
		{
			LeavingWidget->SetRenderOpacity(1.f);
			Cast<UCanvasPanelSlot>(LeavingWidget->Slot)->SetZOrder(1);
		}
	case EMS_TransitionStyle::FadeFromEnteringPage :
		{
			EnterWidget->SetRenderOpacity(0.f);
			Cast<UCanvasPanelSlot>(EnterWidget->Slot)->SetZOrder(1);
		}
	case EMS_TransitionStyle::FloatFromTop :
		{
			EnterWidget->SetRenderTranslation(FVector2D(0.f, -EnterWidget->GetContentFrameSize().Y));
			Cast<UCanvasPanelSlot>(EnterWidget->Slot)->SetZOrder(1);
		}
	case EMS_TransitionStyle::FloatFromBottom :
		{
			EnterWidget->SetRenderTranslation(FVector2D { 0.0f, EnterWidget->GetContentFrameSize().Y });
			Cast<UCanvasPanelSlot>(EnterWidget->Slot)->SetZOrder(1);
		}
	case EMS_TransitionStyle::FloatFromLeft :
		{
			EnterWidget->SetRenderTranslation(FVector2D { -EnterWidget->GetContentFrameSize().X, 0.0f });
			Cast<UCanvasPanelSlot>(EnterWidget->Slot)->SetZOrder(1);
		}
	case EMS_TransitionStyle::FloatFromRight :
		{
			EnterWidget->SetRenderTranslation(FVector2D { EnterWidget->GetContentFrameSize().X, 0.0f });
			Cast<UCanvasPanelSlot>(EnterWidget->Slot)->SetZOrder(1);
		}
	default:
		{
			
		}
	}
	
	EnterWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	//ActivatePreventionCover();

	GetWorld()->GetTimerManager().SetTimer(FadeTimerHandle, this, &AMS_SceneManager::ProcessFade, 0.01f, true);
}

void AMS_SceneManager::ProcessFade()
{
	FadeProgressRate += 0.01f;

	// 나중에 읽고 추가할 예정
	// switch(NewCommand->GetTransitionStyle())
	// {
	// case EMS_TransitionStyle::FadeFromLeavingPage :
	// 	{
	// 		LeavingWidget->SetRenderOpacity(ConvertPageTransitionAnimationCurveValue(1.0 - FadeProgressRate, PageTransitionAnimationCurveType));
	// 	}
	// case EMS_TransitionStyle::FadeFromEnteringPage :
	// 	{
	// 		EnterWidget->SetRenderOpacity(ConvertPageTransitionAnimationCurveValue(FadeProgressRate, PageTransitionAnimationCurveType));
	// 	}
	// case EMS_TransitionStyle::FloatFromTop :
	// 	{
	// 		EnterWidget->SetRenderTranslation(FVector2D { 0.0f, ConvertPageTransitionAnimationCurveValue(1.0 - FadeProgressRate, PageTransitionAnimationCurveType) * -ContentFrameSize.Y });
	// 	}
	// case EMS_TransitionStyle::FloatFromBottom :
	// 	{
	// 		EnterWidget->SetRenderTranslation(FVector2D { 0.0f, ConvertPageTransitionAnimationCurveValue(1.0 - FadeProgressRate, PageTransitionAnimationCurveType) * ContentFrameSize.Y });
	// 	}
	// case EMS_TransitionStyle::FloatFromLeft :
	// 	{
	// 		EnterWidget->SetRenderTranslation(FVector2D { ConvertPageTransitionAnimationCurveValue(1.0 - FadeProgressRate, PageTransitionAnimationCurveType) * -ContentFrameSize.X, 0.0f });
	// 	}
	// case EMS_TransitionStyle::FloatFromRight :
	// 	{
	// 		EnterWidget->SetRenderTranslation(FVector2D { ConvertPageTransitionAnimationCurveValue(1.0 - FadeProgressRate, PageTransitionAnimationCurveType) * ContentFrameSize.X, 0.0f });
	// 	}
	// default:
	// 	{
	// 		
	// 	}
	// }
	
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
	
	
	LeavingWidget->SetVisibility(ESlateVisibility::Hidden);

	const TWeakObjectPtr<UMS_Management> Management = Cast<UMS_Management>(GetOuter());
	MS_CHECK(Management.IsValid());
	const TWeakObjectPtr<UMS_WidgetManager> WidgetManager = Management->GetWidgetManager();
	MS_CHECK(WidgetManager.IsValid());
	WidgetManager->SetCurrentWidget(EnterWidget);
	
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
	
	// Fade In
	StartFade(false);
}

void AMS_SceneManager::HandleLevelLoad()
{
	MS_CHECK(NewCommand);
	MS_CHECK(LevelTable.IsValid());
	
	const FName LevelName = LevelTable->GetLevelName(NewCommand->GetLevelType());
	HandleLoadLevel(LevelName);
}
