// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_GeneralRightExpanderWidget.h"

#include "Button/MS_GeneralButton.h"
#include "Manager_Client/MS_PlayerCameraManager.h"
#include "Manager_Client/MS_SceneManager.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "Widget/Finance/Modal/MS_FinancialManagementWidget.h"
#include "Widget/Market/Modal/MS_MarketOrderCheckModalWidget.h"
#include "Widget/Staff/Modal/MS_StaffManagementWidget.h"
#include "Widget/System/Settings/Modal/MS_SettingModalWidget.h"

void UMS_GeneralRightExpanderWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if(CPP_GoToMarketorTownButton)
	{
		CPP_GoToMarketorTownButton->SetButtonType(EMS_GeneralButtonType::GoTo);
		CPP_GoToMarketorTownButton->GetOnClickedDelegate().AddUObject(this, &UMS_GeneralRightExpanderWidget::OnClickedGotoButton);
	}
	if(CPP_CheckOrderItemButton)
	{
		CPP_CheckOrderItemButton->SetButtonType(EMS_GeneralButtonType::CheckOrderItem);
		CPP_CheckOrderItemButton->GetOnClickedDelegate().AddUObject(this, &UMS_GeneralRightExpanderWidget::OnClickedCheckOrderButton);
	}
	if(CPP_StaffManageButton)
	{
		CPP_StaffManageButton->SetButtonType(EMS_GeneralButtonType::StaffManage);
		CPP_StaffManageButton->GetOnClickedDelegate().AddUObject(this, &UMS_GeneralRightExpanderWidget::OnClickedManageStaffButton);
	}
	if(CPP_SalesDetailButton)
	{
		CPP_SalesDetailButton->SetButtonType(EMS_GeneralButtonType::SalesDetail);
		CPP_SalesDetailButton->GetOnClickedDelegate().AddUObject(this, &UMS_GeneralRightExpanderWidget::OnClickedFinancialIndicatorButton);
	}
	if(CPP_SettingButton)
	{
		CPP_SettingButton->SetButtonType(EMS_GeneralButtonType::Setting);
		CPP_SettingButton->GetOnClickedDelegate().AddUObject(this, &UMS_GeneralRightExpanderWidget::OnClickedSettingButton);
	}
}

void UMS_GeneralRightExpanderWidget::UpdateButton() const
{
	if(CPP_GoToMarketorTownButton)
	{
		CPP_GoToMarketorTownButton->SetButtonType(EMS_GeneralButtonType::GoTo);
	}
}

void UMS_GeneralRightExpanderWidget::OnClickedGotoButton()
{
	if(gSceneMng.GetCurrentLevelType() == EMS_LevelType::MarketLevel)
	{
		CREATE_SCENE_COMMAND(Command);
		Command->SetLevelType(EMS_LevelType::Stage01, GetWorld());
		Command->SetPreviousLevelType(EMS_LevelType::MarketLevel);
		Command->SetFadeOutTransitionType(EMS_TransitionStyle::GradationOut);
		Command->SetFadeInTransitionType(EMS_TransitionStyle::GradationIn);
		Command->SetFadeAnimationType(EMS_FadeAnimationCurveType::Linear);
		Command->SetLoadingWidgetType(EMS_LoadingWidgetType::Default);
		Command->OnFadeInFinishedCallback =  []
		{
			FViewTargetTransitionParams Param;
			Param.BlendTime = 0.f;
			gCameraMng.SwitchViewCamera(EMS_ViewCameraType::QuarterView, Param);
			gWidgetMng.SetGeneralWidget(EMS_LevelType::Stage01);
		};
		gSceneMng.RequestChangeScene(Command);
	}
	else
	{
		CREATE_SCENE_COMMAND(Command);
		Command->SetLevelType(EMS_LevelType::MarketLevel);
		Command->SetPreviousLevelType(EMS_LevelType::Stage01, GetWorld());
		Command->SetFadeOutTransitionType(EMS_TransitionStyle::GradationOut);
		Command->SetFadeInTransitionType(EMS_TransitionStyle::GradationIn);
		Command->SetFadeAnimationType(EMS_FadeAnimationCurveType::Linear);
		Command->SetLoadingWidgetType(EMS_LoadingWidgetType::Default);
		gSceneMng.RequestChangeScene(Command);
	}

	SetVisibility(ESlateVisibility::Collapsed);
}

void UMS_GeneralRightExpanderWidget::OnClickedCheckOrderButton()
{
	FMS_ModalParameter Parameter;
	Parameter.InModalWidget = gWidgetMng.Create_Widget_NotManaging(UMS_MarketOrderCheckModalWidget::GetWidgetPath());
	gWidgetMng.ShowModalWidget(Parameter);

	SetVisibility(ESlateVisibility::Collapsed);
}

void UMS_GeneralRightExpanderWidget::OnClickedManageStaffButton()
{
	FMS_ModalParameter Parameter;
	Parameter.InModalWidget = gWidgetMng.Create_Widget(UMS_StaffManagementWidget::GetWidgetName());
	gWidgetMng.ShowModalWidget(Parameter);
	
	SetVisibility(ESlateVisibility::Collapsed);
}

void UMS_GeneralRightExpanderWidget::OnClickedFinancialIndicatorButton()
{
	FMS_ModalParameter Parameter;
	Parameter.InModalWidget = gWidgetMng.Create_Widget(UMS_FinancialManagementWidget::GetWidgetName());
	gWidgetMng.ShowModalWidget(Parameter);

	SetVisibility(ESlateVisibility::Collapsed);
}

void UMS_GeneralRightExpanderWidget::OnClickedSettingButton()
{
	FMS_ModalParameter Parameter;
	Parameter.InModalWidget = gWidgetMng.Create_Widget(UMS_SettingModalWidget::GetWidgetName());
	gWidgetMng.ShowModalWidget(Parameter);
}
