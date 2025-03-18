// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_AccountWidget.h"

#include "MS_Define.h"
#include "Button/MS_AccountButton.h"
#include "Button/MS_AccountStartButton.h"
#include "Manager_Client/MS_SceneManager.h"
#include "Widget/Lobby/MS_LobbyWidget.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineIdentityInterface.h"


void UMS_AccountWidget::InitWidget(const FName& aTypeName, bool bManaged, bool bActivate)
{
	Super::InitWidget(aTypeName, bManaged, bActivate);

	if(CPP_AccountButton)
	{
		CPP_AccountButton->GetOnClickedDelegate().AddUObject(this, &UMS_AccountWidget::OnClickAccountButton);
	}
}

void UMS_AccountWidget::OnClickAccountButton()
{
#if PLATFORM_ANDROID
	LoginWithGoogle();
#else
	PlayNextStep();
#endif
}

void UMS_AccountWidget::OnGoogleLoginComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId,
	const FString& ErrorStr)
{
	const IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get(TEXT("GooglePlay"));
	if (!OnlineSubsystem)
	{
		return;
	}

	const IOnlineIdentityPtr IdentityInterface = OnlineSubsystem->GetIdentityInterface();
	if (!IdentityInterface.IsValid())
	{
		return;
	}

	// 로그인 성공 여부 확인
	if (bWasSuccessful)
	{
		UE_LOG(LogTemp, Log, TEXT("Google Play Login Success! UserID: %s"), *UserId.ToString());
		PlayNextStep(); // 로그인 성공 후 다음 단계 실행
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Google Play Login Failed: %s"), *ErrorStr);
	}
}

void UMS_AccountWidget::LoginWithGoogle()
{
	const IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get(TEXT("GooglePlay"));
	if (!OnlineSubsystem)
	{
		UE_LOG(LogTemp, Warning, TEXT("GooglePlay OnlineSubsystem is NULL"));
		return;
	}

	const IOnlineIdentityPtr IdentityInterface = OnlineSubsystem->GetIdentityInterface();
	if (!IdentityInterface.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("GooglePlay IdentityInterface is NULL"));
		return;
	}

	// 로그인 콜백 바인딩
	IdentityInterface->OnLoginCompleteDelegates->AddUObject(this, &UMS_AccountWidget::OnGoogleLoginComplete);

	// 로그인 요청
	IdentityInterface->Login(0, FOnlineAccountCredentials());
}

void UMS_AccountWidget::PlayNextStep() const
{
	CPP_AccountButton->GetOnClickedDelegate().RemoveAll(this);
	CPP_AccountButton->SetVisibility(ESlateVisibility::Collapsed);
	
	CREATE_SCENE_COMMAND(Command);
	Command->SetLevelType(EMS_LevelType::LobbyLevel, GetWorld());
	Command->SetPreviousLevelType(EMS_LevelType::AccountLevel, GetWorld());
	Command->SetFadeOutTransitionType(EMS_TransitionStyle::GradationOut);
	Command->SetFadeInTransitionType(EMS_TransitionStyle::GradationIn);
	Command->SetFadeAnimationType(EMS_FadeAnimationCurveType::Linear);
	Command->SetNextWidget(UMS_LobbyWidget::GetWidgetName());
	Command->SetLoadingWidgetType(EMS_LoadingWidgetType::Default);
	Command->SetAllowInteractActor(false);

	gSceneMng.RequestChangeScene(Command);
}
