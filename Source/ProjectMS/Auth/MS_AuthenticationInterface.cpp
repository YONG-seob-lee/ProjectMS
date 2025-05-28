// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_AuthenticationInterface.h"

#include "MS_Define.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
#include "GameUserSettings/MS_GameUserSettings.h"
#include "Interfaces/OnlineIdentityInterface.h"

void FMS_GoogleLoginManager::Login()
{
	const IOnlineSubsystem* OnlineSubsystem = Online::GetSubsystem(nullptr, TEXT("GooglePlay"));
	if(!OnlineSubsystem)
	{
		MS_ERROR(TEXT("GooglePlay subsystem not found"));
		return;
	}
	const IOnlineIdentityPtr IdentityInterface = OnlineSubsystem->GetIdentityInterface();
	if(!IdentityInterface.IsValid())
	{
		MS_ERROR(TEXT("OnlineIdentityInterface not valid"));
		return;
	}
	
	if (IdentityInterface->GetLoginStatus(0) == ELoginStatus::LoggedIn)
	{
		UMS_GameUserSettings* GameUserSettings = Cast<UMS_GameUserSettings>(GEngine->GetGameUserSettings());
		if (!GameUserSettings)
		{
			MS_ERROR(TEXT("GameUserSettings not found"));
			return;
		}
		if (GameUserSettings->IsContinuousLogin())
		{
			IdentityInterface->OnLoginCompleteDelegates->AddRaw(this, &FMS_GoogleLoginManager::OnGoogleLoginComplete);
			IdentityInterface->Login(0, FOnlineAccountCredentials());
		}
		else
		{
			IdentityInterface->OnLogoutCompleteDelegates->AddRaw(this, &FMS_GoogleLoginManager::OnGoogleLogoutComplete);
			IdentityInterface->Logout(0);
		}
	}
	else
	{
		IdentityInterface->OnLoginCompleteDelegates->AddRaw(this, &FMS_GoogleLoginManager::OnGoogleLoginComplete);
		IdentityInterface->Login(0, FOnlineAccountCredentials());
	}
}

void FMS_GoogleLoginManager::Logout()
{
	const IOnlineSubsystem* OnlineSubsystem = Online::GetSubsystem(nullptr, TEXT("GooglePlay"));
	if (!OnlineSubsystem)
	{
		return;
	}

	const IOnlineIdentityPtr IdentityInterface = OnlineSubsystem->GetIdentityInterface();
	if (!IdentityInterface.IsValid())
	{
		MS_ERROR(TEXT("OnlineIdentityInterface not valid"));
		return;
	}

	if (IdentityInterface->GetLoginStatus(0) == ELoginStatus::LoggedIn)
	{
		IdentityInterface->OnLogoutCompleteDelegates->AddRaw(this, &FMS_GoogleLoginManager::OnGoogleLogoutComplete);
		IdentityInterface->Logout(0);
	}
	else
	{
		MS_ERROR(TEXT("Google Play is not logged in."));
	}
}

bool FMS_GoogleLoginManager::IsLoginedIn() const
{
	const IOnlineSubsystem* OnlineSubsystem = Online::GetSubsystem(nullptr, TEXT("GooglePlay"));
	if (!OnlineSubsystem)
	{
		return false;
	}

	const IOnlineIdentityPtr IdentityInterface = OnlineSubsystem->GetIdentityInterface();
	if (!IdentityInterface.IsValid())
	{
		return false;
	}

	return IdentityInterface->GetLoginStatus(0) == ELoginStatus::LoggedIn;
}

void FMS_GoogleLoginManager::OnGoogleLoginComplete(int32 _Index, bool bSuccessful, const FUniqueNetId& _UserId, const FString& _ErrorString)
{
	const IOnlineSubsystem* OnlineSubsystem = Online::GetSubsystem(nullptr, TEXT("GooglePlay"));
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
	if (bSuccessful)
	{
		UE_LOG(LogTemp, Log, TEXT("Google Play Login Success! UserID: %s"), *_UserId.ToString());
		if (OnGoogleLoginCallback)
		{
			OnGoogleLoginCallback();
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Google Play Login Failed: %s"), *_ErrorString);
	}
}

void FMS_GoogleLoginManager::OnGoogleLogoutComplete(int32 _MaxLocalPlayers, bool bOnLogoutComplete)
{
	MS_LOG(TEXT("Google Logout Complete. Success : %s"), bOnLogoutComplete ? TEXT("true") : TEXT("false"));

	Login();
}
