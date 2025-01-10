#include "MS_TouchWidget.h"

#include "NiagaraSystemWidget.h"

void UMS_TouchWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	RebuildTouchWidget();
}

void UMS_TouchWidget::RebuildTouchWidget()
{
	if(CPP_TouchEffectWidget)
	{
		CPP_TouchEffectWidget->RebuildWidget();
	}
}

void UMS_TouchWidget::PlayActive()
{
	CPP_TouchEffectWidget->ActivateSystem(true);
}
