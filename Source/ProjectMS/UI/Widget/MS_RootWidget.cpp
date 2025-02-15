// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_RootWidget.h"

#include "MS_Define.h"
#include "Button/MS_GeneralButton.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Dialog/MS_DialogWidget.h"
#include "Loading/MS_DefaultLoadingWidget.h"
#include "Manager_Client/MS_SoundManager.h"
#include "System/MS_ToastWidget.h"
#include "System/Modal/MS_ModalWidget.h"
#include "System/Rotate/MS_RotateWidget.h"
#include "WidgetComponent/MS_CanvasPanel.h"
#include "WidgetComponent/MS_WidgetSwitcher.h"

namespace MessageType
{
	constexpr int32 Toast  = 0;
}

namespace InterfaceType
{
	constexpr int32 Rotate = 0;
	constexpr int32 Modal = 1;
}

UMS_RootWidget::UMS_RootWidget(const FObjectInitializer& aObjectInitializer) :Super(aObjectInitializer)
{
}

void UMS_RootWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	const TObjectPtr<UCanvasPanelSlot> CanvasPanelSlot = Cast<UCanvasPanelSlot>(CPP_PreventionCoverImage->Slot);
	MS_CHECK(CanvasPanelSlot);
	CanvasPanelSlot->SetZOrder(1000);
	
	CPP_LoadingPanel->SetVisibility(ESlateVisibility::Collapsed);
	CPP_MessagePanel->SetVisibility(ESlateVisibility::Collapsed);
	CPP_RotateWidget->SetVisibility(ESlateVisibility::Collapsed);
	CPP_ModalWidget->SetVisibility(ESlateVisibility::Collapsed);
	CPP_GeneralWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	CPP_GeneralWidget->SetRenderOpacity(0.001f);
}

void UMS_RootWidget::OnRuntimeInitialize()
{
	Super::OnRuntimeInitialize();
	
	CutoutFrameSize = CPP_CutoutFrameCanvasPanel->GetCachedGeometry().GetLocalSize();
	ContentFrameSize = CPP_ContentFrameCanvasPanel->GetCachedGeometry().GetLocalSize();
}

void UMS_RootWidget::AttachContentWidget(const TObjectPtr<UMS_Widget>& aContentWidget) const
{
	MS_CHECK(CPP_ContentFrameCanvasPanel);

	if(CPP_ContentFrameCanvasPanel->HasChild(aContentWidget) == false)
	{
		CPP_ContentFrameCanvasPanel->AddChild(aContentWidget);
		const TObjectPtr<UCanvasPanelSlot> CanvasPanelSlot = Cast<UCanvasPanelSlot>(aContentWidget->Slot);
		CanvasPanelSlot->SetAnchors(FAnchors(0.f, 0.f, 1.f, 1.f));
		CanvasPanelSlot->SetPosition(FVector2D::ZeroVector);
		CanvasPanelSlot->SetOffsets(FMargin(0.f, 0.f));
	}
}

void UMS_RootWidget::RefreshContentCanvas() const
{
	MS_CHECK(CPP_ContentFrameCanvasPanel);
	CPP_ContentFrameCanvasPanel->ClearChildren();
}

void UMS_RootWidget::ActivatePreventionCover(bool bShow) const
{
	CPP_PreventionCoverImage->SetVisibility(bShow ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Hidden);
}

void UMS_RootWidget::SetContentWidgetRender(EMS_TransitionStyle aTransitionStyle) const
{
	switch(aTransitionStyle)
	{
	case EMS_TransitionStyle::GradationIn :
		{
			CPP_LoadingPanel->SetRenderOpacity(1.f);
		Cast<UCanvasPanelSlot>(CPP_LoadingPanel->Slot)->SetZOrder(1);
			break;
		}
	case EMS_TransitionStyle::GradationOut :
		{
			CPP_LoadingPanel->SetRenderOpacity(0.f);
		Cast<UCanvasPanelSlot>(CPP_LoadingPanel->Slot)->SetZOrder(1);
			break;
		}
	case EMS_TransitionStyle::FloatFromTop :
		{
			CPP_LoadingPanel->SetRenderTranslation(FVector2D(0.f, -GetContentFrameSize().Y));
		Cast<UCanvasPanelSlot>(CPP_LoadingPanel->Slot)->SetZOrder(1);
			break;
		}
	case EMS_TransitionStyle::FloatFromBottom :
		{
			CPP_LoadingPanel->SetRenderTranslation(FVector2D { 0.f, GetContentFrameSize().Y });
		Cast<UCanvasPanelSlot>(CPP_LoadingPanel->Slot)->SetZOrder(1);
			break;
		}
	case EMS_TransitionStyle::FloatFromLeft :
		{
			CPP_LoadingPanel->SetRenderTranslation(FVector2D { -GetContentFrameSize().X, 0.f });
		Cast<UCanvasPanelSlot>(CPP_LoadingPanel->Slot)->SetZOrder(1);
			break;
		}
	case EMS_TransitionStyle::FloatFromRight :
		{
			CPP_LoadingPanel->SetRenderTranslation(FVector2D { GetContentFrameSize().X, 0.f });
		Cast<UCanvasPanelSlot>(CPP_LoadingPanel->Slot)->SetZOrder(1);
			break;
		}
	default:
		{
			
		}
	}
	CPP_LoadingPanel->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	//ActivatePreventionCover(true);
}

void UMS_RootWidget::SetContentWidgetTransition(EMS_TransitionStyle aTransitionStyle, EMS_FadeAnimationCurveType aFadeAnimationCurveType, float aFadeProgressRate) const
{
	MS_CHECK(CPP_LoadingPanel);
	
	switch(aTransitionStyle)
	{
	case EMS_TransitionStyle::GradationIn :
		{
			CPP_LoadingPanel->SetRenderOpacity(ConvertFadeAnimationCurveValue(1.f - aFadeProgressRate, aFadeAnimationCurveType));
			break;
		}
	case EMS_TransitionStyle::GradationOut :
		{
			CPP_LoadingPanel->SetRenderOpacity(ConvertFadeAnimationCurveValue(aFadeProgressRate, aFadeAnimationCurveType));
			break;
		}
	case EMS_TransitionStyle::FloatFromTop :
		{
			CPP_LoadingPanel->SetRenderTranslation(FVector2D { 0.f, ConvertFadeAnimationCurveValue(1.f - aFadeProgressRate, aFadeAnimationCurveType) * -GetContentFrameSize().Y });
			break;
		}
	case EMS_TransitionStyle::FloatFromBottom :
		{
			CPP_LoadingPanel->SetRenderTranslation(FVector2D { 0.f, ConvertFadeAnimationCurveValue(1.f - aFadeProgressRate, aFadeAnimationCurveType) * GetContentFrameSize().Y });
			break;
		}
	case EMS_TransitionStyle::FloatFromLeft :
		{
			CPP_LoadingPanel->SetRenderTranslation(FVector2D { ConvertFadeAnimationCurveValue(1.f - aFadeProgressRate, aFadeAnimationCurveType) * -GetContentFrameSize().X, 0.f });
			break;
		}
	case EMS_TransitionStyle::FloatFromRight :
		{
			CPP_LoadingPanel->SetRenderTranslation(FVector2D { ConvertFadeAnimationCurveValue(1.f - aFadeProgressRate, aFadeAnimationCurveType) * GetContentFrameSize().X, 0.f });
			break;
		}
	default:
		{
			
		}
	}
}

void UMS_RootWidget::ResetCanvasZOrder() const
{
	const TObjectPtr<UCanvasPanelSlot> ContentSlot = Cast<UCanvasPanelSlot>(CPP_ContentFrameCanvasPanel->Slot);
	MS_CHECK(ContentSlot);
	ContentSlot->SetZOrder(0);
	
	const TObjectPtr<UCanvasPanelSlot> LoadingSlot = Cast<UCanvasPanelSlot>(CPP_LoadingPanel->Slot);
	MS_CHECK(LoadingSlot);
	LoadingSlot->SetZOrder(0);
}

void UMS_RootWidget::ResetToastPanel() const
{
	if(CPP_MessagePanel)
	{
		CPP_MessagePanel->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UMS_RootWidget::ShowToastMessage(const FString& Message) const
{
	if(CPP_ToastWidget->IsPlayingAnimation())
	{
		return;
	}

	CPP_ToastWidget->SetToastMsg(Message);
	
	CPP_MessagePanel->SetVisibility(ESlateVisibility::HitTestInvisible);
	CPP_MessageWidgetSwitcher->SetActiveWidgetIndex(MessageType::Toast);
		
	// 추후 인수를 토스트위젯에 추가하여 대입
	CPP_ToastWidget->PlayAnimationByName(DefaultWidgetAnimation::Appearance);
}

void UMS_RootWidget::ShowRotateWidget() const
{
	CPP_RotateWidget->SetVisibility(CPP_RotateWidget->IsVisible() ? ESlateVisibility::Collapsed : ESlateVisibility::SelfHitTestInvisible);	
}

void UMS_RootWidget::ShowModalWidget(const FMS_ModalParameter& aModalParameter) const
{
	CPP_ModalWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	CPP_ModalWidget->SetModal(aModalParameter);

	if(aModalParameter.InModalPosition != FVector2D::ZeroVector)
	{
		CPP_ModalWidget->SetInModalPosition(aModalParameter.InModalPosition);
	}
}

void UMS_RootWidget::CloseModalWidget() const
{
	CPP_ModalWidget->CloseModal();
}

void UMS_RootWidget::RequestPassTimer() const
{
	CPP_GeneralWidget->RequestPassTimer();
}

void UMS_RootWidget::RequestDialog(const TArray<FMS_DialogParameter>& aDialogParameters) const
{
	CPP_MessagePanel->SetVisibility(ESlateVisibility::Visible);

	FMS_DialogParameter LastParameter = aDialogParameters.Last();
	LastParameter.SetDialogEndCallback([this](){CPP_MessagePanel->SetVisibility(ESlateVisibility::Collapsed);});
	CPP_DialogWidget->RequestDialog(aDialogParameters);
}

void UMS_RootWidget::Test(int32 test)
{
	CPP_GeneralWidget->Test(test);
}

void UMS_RootWidget::SetGeneralWidget(EMS_LevelType aLevelType) const
{
	if(aLevelType < EMS_LevelType::LobbyLevel)
	{
		// 위젯 애니메이션에 입혀놓은 사운드웨이브가 Collapsed 또는 Hidden 일 때 일시정지하면서 이중창 삼중창으로 오버랩되는 현상 개선 목적으로 일단 주석처리.
		CPP_GeneralWidget->SetRenderOpacity(0.001f);
		CPP_GeneralWidget->SetType(EMS_GeneralWidgetType::None);
	}
	else if(aLevelType == EMS_LevelType::LobbyLevel)
	{
		CPP_GeneralWidget->SetRenderOpacity(1.f);
		CPP_GeneralWidget->SetType(EMS_GeneralWidgetType::Lobby);
	}
	else if(aLevelType == EMS_LevelType::Stage01 || aLevelType == EMS_LevelType::Stage02 || aLevelType == EMS_LevelType::Stage03)
	{
		CPP_GeneralWidget->SetRenderOpacity(1.f);
		CPP_GeneralWidget->SetType(EMS_GeneralWidgetType::Town);
	}
	else if(aLevelType == EMS_LevelType::MarketLevel)
	{
		CPP_GeneralWidget->SetRenderOpacity(1.f);
		CPP_GeneralWidget->SetType(EMS_GeneralWidgetType::Market);
	}
	else
	{
		CPP_GeneralWidget->SetRenderOpacity(0.001f);
		CPP_GeneralWidget->SetType(EMS_GeneralWidgetType::None);
	}
}

void UMS_RootWidget::SetBGMAnimation(EMS_LevelType aLevelType) const
{
	CPP_GeneralWidget->StopAllAnimations();
	
	if(aLevelType == EMS_LevelType::LobbyLevel || aLevelType == EMS_LevelType::Stage01 || aLevelType == EMS_LevelType::Stage02 || aLevelType == EMS_LevelType::Stage03)
	{
		if(CPP_GeneralWidget->IsPlayingAnimation() == false)
		{
			CPP_GeneralWidget->PlayAnimationByName(BGM::Town, 0.f, 50000);
		}
	}
	else if(aLevelType == EMS_LevelType::MarketLevel)
	{
		CPP_GeneralWidget->PlayAnimationByName(BGM::Market, 0.f, 50000);
	}
	else
	{
		CPP_GeneralWidget->StopAllAnimations();
	}
}

void UMS_RootWidget::ShowGeneralWidget(bool bShow) const
{
	CPP_GeneralWidget->SetRenderOpacity(bShow ? 1.f : 0.001f);
}
