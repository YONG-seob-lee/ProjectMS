// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_Button.h"

#include "MS_Define.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/NamedSlot.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "Widget/System/Toturial/MS_DescriptionWidget.h"

UMS_Button::UMS_Button()
{
}

UMS_Button::~UMS_Button()
{
}

void UMS_Button::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMS_Button::NativeOnCurrentTextStyleChanged()
{
	Super::NativeOnCurrentTextStyleChanged();
}

#if WITH_EDITOR
const FText UMS_Button::GetPaletteCategory()
{
	return FText::FromString("MS Custom");
}
#endif

void UMS_Button::OnHoverJoyStick()
{
	HandleFocusReceived();
}

void UMS_Button::UnHoverJoyStick()
{
	NativeOnUnhovered();
}

void UMS_Button::PlayTutorial(const FString& Desc, const FString& SubDesc)
{
	const TObjectPtr<UNamedSlot> NamedSlot = GetNamedSlot();
	if(!NamedSlot)
	{
		return;
	}
	const TObjectPtr<UMS_DescriptionWidget> DescWidget = Cast<UMS_DescriptionWidget>(gWidgetMng.Create_Widget_NotManaging(UMS_DescriptionWidget::GetWidgetPath()));
	if(!DescWidget)
	{
		return; 
	}
	
	NamedSlot->SetContent(DescWidget);
	RePositionNamedSlot(NamedSlot->Slot);
	DescWidget->Start(TutorialDirection, Desc, SubDesc);
}

void UMS_Button::SetDelegates()
{
	OnClicked().AddUObject(this, &UMS_Button::OnClick);
	OnPressed().AddUObject(this, &UMS_Button::OnPress);
	OnReleased().AddUObject(this, &UMS_Button::OnRelease);
	OnHovered().AddUObject(this, &UMS_Button::OnHover);
	OnUnhovered().AddUObject(this, &UMS_Button::OnUnHover);
}

void UMS_Button::OnClick()
{
	if (IsUseClockedDelay())
	{
		const TObjectPtr<UWorld> World = GetWorld();
		MS_CHECK(World);

		const float CurrentClickedTime = GetWorld() == nullptr ? 0.f : GetWorld()->GetUnpausedTimeSeconds();
		if (LastClickedTime + ClickedDelayTime >= CurrentClickedTime)
		{
			MS_OnClickedInDelayTimeDelegate.Broadcast();
			return;
		}
		LastClickedTime = GetWorld() == nullptr ? 0.f : GetWorld()->GetUnpausedTimeSeconds();
	}

	if (IsUseLongPressedEvent() == false)
	{
		MS_OnClickedDelegate.Broadcast();
	}
}

void UMS_Button::OnPress()
{
	if(IsUseLongPressedEvent())
	{
		FTimerManager& TimerManager = GetWorld()->GetTimerManager();
		TimerManager.SetTimer(PressTimerHandle, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			MS_OnLongPressedDelegate.Broadcast();
		}), LongPressedTime, false);
	}
	MS_OnPressedDelegate.Broadcast();
}

void UMS_Button::OnRelease()
{
	MS_OnReleasedDelegate.Broadcast();

	if(IsUseLongPressedEvent())
	{
		FTimerManager& TimerManager = GetWorld()->GetTimerManager();
		if(TimerManager.IsTimerActive(PressTimerHandle))
		{
			TimerManager.ClearTimer(PressTimerHandle);
		}
	}
}

void UMS_Button::OnHover()
{
	MS_OnHoveredDelegate.Broadcast();
}

void UMS_Button::OnUnHover()
{
	MS_OnUnhoveredDelegate.Broadcast();
}

TObjectPtr<UNamedSlot> UMS_Button::GetNamedSlot() const
{
	if(UWidget* TutorialSlot = GetWidgetFromName(Tutorial::SlotName))
	{
		return Cast<UNamedSlot>(TutorialSlot);
	}

	return nullptr;
}

void UMS_Button::RePositionNamedSlot(const TObjectPtr<UPanelSlot>& NamedSlot) const
{
	const TObjectPtr<UCanvasPanelSlot> NamedPanelSlot = Cast<UCanvasPanelSlot>(NamedSlot);
	if(!NamedPanelSlot)
	{
		return;
	}
	NamedPanelSlot->SetSize(Tutorial::DefaultSize);
	
	if(TutorialDirection == EMS_TutorialDirection::UpToRight)
	{
		NamedPanelSlot->SetAnchors(FAnchors(1.f, 0.f, 1.f, 0.f));
		NamedPanelSlot->SetAlignment(FVector2D(0.f, 1.f));
	}
	else if(TutorialDirection == EMS_TutorialDirection::DownToRight)
	{
		NamedPanelSlot->SetAnchors(FAnchors(1.f, 1.f, 1.f, 1.f));
		NamedPanelSlot->SetAlignment(FVector2D(0.f, 0.f));
	}
	else if(TutorialDirection == EMS_TutorialDirection::UpToLeft)
	{
		NamedPanelSlot->SetAnchors(FAnchors(0.f, 0.f, 0.f, 0.f));
		NamedPanelSlot->SetAlignment(FVector2D(1.f, 1.f));
	}
	else if(TutorialDirection == EMS_TutorialDirection::DownToLeft)
	{
		NamedPanelSlot->SetAnchors(FAnchors(0.f, 1.f, 0.f, 1.f));
		NamedPanelSlot->SetAlignment(FVector2D(1.f,0.f));
	}
}
