#include "MS_TouchWidget.h"

#include "MS_Define.h"
#include "NiagaraSystemWidget.h"
#include "NiagaraUIComponent.h"

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
	if(bIsActive == false)
	{
		return;
	}
	
	if(CPP_TouchEffectWidget->GetNiagaraComponent()->IsActive() == false)
	{
		if(OnFinishedParticleRendererCallback)
		{
			OnFinishedParticleRendererCallback();
			bIsActive = false;
		}
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

void UMS_TouchWidget::PlayActive()
{
	GetWorld()->GetTimerManager().SetTimer(ActiveHandle, [this](){bIsActive = true; }, 0.2f, false);
	
	CPP_TouchEffectWidget->ActivateSystem(true);
}
