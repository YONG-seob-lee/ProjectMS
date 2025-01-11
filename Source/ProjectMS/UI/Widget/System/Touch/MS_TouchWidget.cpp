#include "MS_TouchWidget.h"

#include "MS_Define.h"
#include "NiagaraSystemWidget.h"

void UMS_TouchWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMS_TouchWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UMS_TouchWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	ElapsedTime += InDeltaTime;
	
	if(ElapsedTime >= 5.f)
	{
		MS_DeleteObject(this);
	}
}

void UMS_TouchWidget::RebuildTouchWidget() const
{
	if(CPP_TouchEffectWidget)
	{
		CPP_TouchEffectWidget->RebuildWidget();
	}
}

void UMS_TouchWidget::ReleasedNiagaraActor() const
{
	if(CPP_TouchEffectWidget)
	{
		CPP_TouchEffectWidget->ReleaseSlateResources(true);
	}
}

void UMS_TouchWidget::PlayActive() const
{	
	CPP_TouchEffectWidget->ActivateSystem(true);
}
