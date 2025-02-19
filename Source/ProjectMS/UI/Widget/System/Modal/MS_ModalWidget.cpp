// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ModalWidget.h"

#include "MS_Define.h"
#include "Button/MS_Button.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Manager_Client/MS_InputManager.h"
#include "Manager_Client/MS_ScheduleManager.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "Widget/Market/Modal/MS_MarketStartModal.h"

void UMS_ModalWidget::NativeConstruct()
{
	Super::NativeConstruct();

	FillDefaultAnimations();
	if(CPP_BlurButton)
	{
		CPP_BlurButton->GetOnClickedDelegate().AddWeakLambda(this, [this]()
		{
			gWidgetMng.CloseModalWidget();
		});
	}
}

void UMS_ModalWidget::OnAnimFinished(const FName& aAnimName)
{
	Super::OnAnimFinished(aAnimName);

	
	if(aAnimName == TEXT("CloseModal"))
	{
		if(OnCloseModalWidgetCallback)
		{
			OnCloseModalWidgetCallback();
		}

		gInputMng.SetAllowGlide(true);
		
		const TObjectPtr<UMS_Widget> InWidget = Cast<UMS_Widget>(CPP_InModalPanel->GetChildAt(0));
		if(!InWidget)
		{
			return;
		}
		gWidgetMng.DestroyWidget(InWidget);
		SetModalInternal(gWidgetMng.Create_Widget_NotManaging(DefaultModal::InModalWidgetPath));
	}
}

void UMS_ModalWidget::SetModal(const FMS_ModalParameter& aModalParameter)
{
	SetModalInternal(aModalParameter.InModalWidget);
	bPlayCloseAnimation = aModalParameter.bPlayCloseAnimation;

	OnCloseModalWidgetCallback = aModalParameter.OnCloseWidgetCallback;
	if(aModalParameter.bPlayOpenAnimation)
	{
		PlayAnimationByName(ModalWidgetAnimation::Open);
	}
}

void UMS_ModalWidget::CloseModal(const TFunction<void()>& _OnCloseModalWidgetCallback)
{
	if(bPlayCloseAnimation)
	{
		OnCloseModalWidgetCallback = _OnCloseModalWidgetCallback;
		PlayAnimationByName(ModalWidgetAnimation::Close);
	}
	else
	{
		OnCloseModalWidgetCallback = _OnCloseModalWidgetCallback;
		SetVisibility(ESlateVisibility::Collapsed);
		SetModalInternal(gWidgetMng.Create_Widget_NotManaging(DefaultModal::InModalWidgetPath));
	}

}

void UMS_ModalWidget::SetInModalPosition(const FVector2D& aInModalPosition) const
{
	if(UCanvasPanelSlot* aSlot = Cast<UCanvasPanelSlot>(CPP_InModalPanel->Slot))
	{
		aSlot->SetPosition(aInModalPosition);
	}
}

void UMS_ModalWidget::SetModalInternal(const TObjectPtr<UMS_Widget>& aNewWidget)
{
	if(!aNewWidget)
	{
		return;
	}
	CPP_InModalPanel->ClearChildren();
	CPP_InModalPanel->AddChild(aNewWidget);
	
	if(UCanvasPanelSlot* aSlot = Cast<UCanvasPanelSlot>(aNewWidget->Slot))
	{
		aSlot->SetSize(FVector2D(1440.f, 810.f));
		//aSlot->SetAnchors(FAnchors::Maximum);
	}
}
