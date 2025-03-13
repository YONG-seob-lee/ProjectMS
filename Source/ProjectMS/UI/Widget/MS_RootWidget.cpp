// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_RootWidget.h"

#include "MS_Define.h"
#include "Button/MS_GeneralButton.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Dialog/MS_DialogWidget.h"
#include "Loading/MS_DefaultLoadingWidget.h"
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
}

void UMS_RootWidget::OnRuntimeInitialize()
{
	Super::OnRuntimeInitialize();
	
	CutoutFrameSize = CPP_CutoutFrameCanvasPanel->GetCachedGeometry().GetLocalSize();
	CPP_CutoutFrameCanvasPanel->SetVisibility(ESlateVisibility::Collapsed);
	ContentFrameSize = CPP_ContentFrameCanvasPanel->GetCachedGeometry().GetLocalSize();
}

void UMS_RootWidget::AttachContentWidget(const TObjectPtr<UMS_Widget>& aContentWidget) const
{
	if(aContentWidget == nullptr)
	{
		return;
	}

	if(CPP_ContentFrameCanvasPanel && CPP_ContentFrameCanvasPanel->HasChild(aContentWidget) == false)
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

void UMS_RootWidget::UpdateLoadingImage() const
{
	if(CPP_LoadingWidget)
	{
		CPP_LoadingWidget->UpdateLoadingImage();
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

void UMS_RootWidget::CloseModalWidget(const TFunction<void()>& _OnCloseModalWidgetCallback) const
{
	CPP_ModalWidget->CloseModal(_OnCloseModalWidgetCallback);
}

void UMS_RootWidget::RequestDialog(const TArray<FMS_DialogParameter>& aDialogParameters) const
{
	CPP_MessagePanel->SetVisibility(ESlateVisibility::Visible);

	FMS_DialogParameter LastParameter = aDialogParameters.Last();
	LastParameter.SetDialogEndCallback([this](){CPP_MessagePanel->SetVisibility(ESlateVisibility::Collapsed);});
	CPP_DialogWidget->RequestDialog(aDialogParameters);
}

void UMS_RootWidget::ShowContentsWidget(bool bShow) const
{
	CPP_ContentFrameCanvasPanel->SetVisibility(bShow ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Collapsed);
}
