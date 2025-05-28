// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_AccountWidget.h"

#include "MS_Define.h"
#include "Auth/MS_AuthenticationInterface.h"
#include "Button/MS_AccountButton.h"
#include "Button/MS_AccountStartButton.h"
#include "Manager_Client/MS_SceneManager.h"
#include "Subsystem/MS_LoginSubSystem.h"
#include "Widget/Lobby/MS_LobbyWidget.h"


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
	ULocalPlayer* LP = GetWorld()->GetFirstLocalPlayerFromController();
	if (!LP)
	{
		return;
	}

	UMS_LoginSubSystem* LoginSS = LP->GetSubsystem<UMS_LoginSubSystem>();
	if (!LoginSS)
	{
		return;
	}

	TWeakPtr<FMS_GoogleLoginManager> GoogleLoginManager = StaticCastSharedPtr<FMS_GoogleLoginManager>(LoginSS->GetAuthManager());
	if (GoogleLoginManager.IsValid())
	{
		GoogleLoginManager.Pin().Get()->SetOnGoogleLoginFunc([this]() { PlayNextStep(); });
		GoogleLoginManager.Pin().Get()->Login();
	}
}

void UMS_AccountWidget::PlayNextStep() const
{
	ULocalPlayer* LP = GetWorld()->GetFirstLocalPlayerFromController();
	if (!LP)
	{
		return;
	}

	UMS_LoginSubSystem* LoginSS = LP->GetSubsystem<UMS_LoginSubSystem>();
	if (!LoginSS)
	{
		return;
	}

	TWeakPtr<FMS_GoogleLoginManager> GoogleLoginManager = StaticCastSharedPtr<FMS_GoogleLoginManager>(LoginSS->GetAuthManager());
	if (GoogleLoginManager.IsValid())
	{
		GoogleLoginManager.Pin().Get()->SetOnGoogleLoginFunc(nullptr );
	}
	
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
