#include "MS_ToastWidget.h"

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
