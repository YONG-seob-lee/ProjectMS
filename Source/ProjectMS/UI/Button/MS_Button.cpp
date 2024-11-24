// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_Button.h"

#include "MS_Define.h"

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
