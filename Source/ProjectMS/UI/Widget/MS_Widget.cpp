// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_Widget.h"

#include "MovieScene.h"
#include "MS_Define.h"
#include "Animation/WidgetAnimation.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "System/Toturial/MS_DescriptionWidget.h"
#include "WidgetComponent/MS_NamedSlot.h"

UMS_Widget::UMS_Widget(const FObjectInitializer& aObjectInitializer) : Super(aObjectInitializer)
{
	SetForegroundColor(FSlateColor(FColor(255, 255, 255, 255)));
}

void UMS_Widget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UMS_Widget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMS_Widget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UMS_Widget::InitWidget(const FName& aTypeName, bool bManaged, bool bAttachToRoot /* = true */)
{
	IsManaged = bManaged;
	
	FillDefaultAnimations();

	if(bManaged)
	{
		Active(true, bAttachToRoot);
	}
}

void UMS_Widget::FinishWidget()
{
	StopAllAnimations();
}

void UMS_Widget::NativeTick(const FGeometry& aMyGeometry, float aInDeltaTime)
{
	Super::NativeTick(aMyGeometry, aInDeltaTime);
}

void UMS_Widget::PlayTutorial(const FText& Desc, const FText& SubDesc)
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

void UMS_Widget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
	Super::OnAnimationFinished_Implementation(Animation);
	
	OnAnimFinished(FName(Animation->GetMovieScene()->GetName()));
}

void UMS_Widget::OnRuntimeInitialize()
{
}

void UMS_Widget::Active(bool bActive, bool bAttachToRoot/* = true */)
{
	if(bAttachToRoot)
	{
		gWidgetMng.AttachToRoot(this);
	}
	else
	{
		AddToViewport(bActive ? ResourceWidgetInfo.zOrder : 0);
	}
	
	if(IsVisible())
	{
		if(IsExistAnim(DefaultWidgetAnimation::Appearance) == true)
		{
			PlayAnimationByName(DefaultWidgetAnimation::Appearance);
		}

		if(bActive == false)
		{
			SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void UMS_Widget::FillDefaultAnimations()
{
	WidgetAnimations.Empty();

	FProperty* Property = GetClass()->PropertyLink;
	while(Property != nullptr)
	{
		if(Property->GetClass() == FObjectProperty::StaticClass())
		{
			if(const FObjectProperty* ObjectProperty = CastField<FObjectProperty>(Property))
			{
				if(ObjectProperty->PropertyClass == UWidgetAnimation::StaticClass())
				{
					UWidgetAnimation* WidgetAnimObject = Cast<UWidgetAnimation>(ObjectProperty->GetObjectPropertyValue_InContainer(this));

					if(WidgetAnimObject && WidgetAnimObject->MovieScene != nullptr)
					{
						WidgetAnimations.Emplace(WidgetAnimObject->GetMovieScene()->GetName(), WidgetAnimObject);
					}
				}
			}
		}
		Property = Property->PropertyLinkNext;
	}
}

void UMS_Widget::OnAnimFinished(const FName& aAnimName)
{
	if(aAnimName == DefaultWidgetAnimation::Appearance)
	{
		if(GetAnimationByName(DefaultWidgetAnimation::Idle))
		{
			PlayAnimationByName(DefaultWidgetAnimation::Idle, 0.f, 0);
		}
	}
}

TObjectPtr<UWidgetAnimation> UMS_Widget::GetAnimationByName(FName aAnimName) const
{
	if (WidgetAnimations.Contains(aAnimName))
	{
		TObjectPtr<UWidgetAnimation> const* pWidgetAnim = WidgetAnimations.Find(aAnimName);
		return pWidgetAnim == nullptr ? nullptr : *pWidgetAnim;
	}

	return nullptr;
}

void UMS_Widget::PlayAnimationByName(FName aName, float aStartTime, int32 aLoopCount, EUMGSequencePlayMode::Type aPlayType, float aSpeed)
{
	if(const TObjectPtr<UWidgetAnimation> WidgetAnimation = GetAnimationByName(aName))
	{
		PlayAnimation(WidgetAnimation, aStartTime, aLoopCount, aPlayType, aSpeed);
	}
}

void UMS_Widget::StopAnimationByName(FName aName)
{
	if(const TObjectPtr<UWidgetAnimation> WidgetAnimation = GetAnimationByName(aName))
	{
		StopAnimation(WidgetAnimation);
	}
}

bool UMS_Widget::IsExistAnim(FName aAnimName) const
{
	const TObjectPtr<UWidgetAnimation> WidgetAnim = GetAnimationByName(aAnimName);

	return WidgetAnim != nullptr;
}

bool UMS_Widget::IsAnimationPlayingByName(const FName& aName) const
{
	if(const TObjectPtr<UWidgetAnimation> WidgetAnimation = GetAnimationByName(aName))
	{
		return IsAnimationPlaying(WidgetAnimation);
	}

	return false;
}

TObjectPtr<UNamedSlot> UMS_Widget::GetNamedSlot() const
{
	if(UWidget* TutorialSlot = GetWidgetFromName(Tutorial::SlotName))
	{
		return Cast<UNamedSlot>(TutorialSlot);
	}

	return nullptr;
}

void UMS_Widget::RePositionNamedSlot(const TObjectPtr<UPanelSlot>& NamedSlot) const
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
