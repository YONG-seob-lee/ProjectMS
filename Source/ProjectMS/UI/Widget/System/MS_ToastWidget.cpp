#include "MS_ToastWidget.h"

#include "Components/TextBlock.h"
#include "Widget/MS_RootWidget.h"

void UMS_ToastWidget::NativeConstruct()
{
	Super::NativeConstruct();

	FillDefaultAnimations();
}

void UMS_ToastWidget::OnAnimFinished(const FName& aAnimName)
{
	Super::OnAnimFinished(aAnimName);

	if(aAnimName == DefaultWidgetAnimation::Appearance)
	{
		PlayAnimationByName(DefaultWidgetAnimation::Idle);
	}
	else if(aAnimName == DefaultWidgetAnimation::Idle)
	{
		PlayAnimationByName(DefaultWidgetAnimation::DisAppearance);
	}
	else if(aAnimName == DefaultWidgetAnimation::DisAppearance)
	{
		if(const TObjectPtr<UMS_RootWidget> RootWidget = Cast<UMS_RootWidget>(GetOuter()))
		{
			RootWidget->ResetToastPanel();
		}
	}
}

void UMS_ToastWidget::SetToastMsg(const FString& aMessage) const
{
	CPP_ToastText->SetText(aMessage == TEXT("") ? FText::FromString(TEXT("추후 업데이트 예정입니다.")) : FText::FromString(aMessage));
}
