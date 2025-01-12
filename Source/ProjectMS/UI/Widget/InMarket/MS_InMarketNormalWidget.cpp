#include "MS_InMarketNormalWidget.h"

#include "Button/MS_Button.h"
#include "Manager_Client/MS_ModeManager.h"


void UMS_InMarketNormalWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	CPP_ConstructButton->GetOnClickedDelegate().AddUObject(this, &UMS_InMarketNormalWidget::OnClickConstructButton);
}

void UMS_InMarketNormalWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMS_InMarketNormalWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UMS_InMarketNormalWidget::OnClickConstructButton()
{
	gModeMng.ChangeState(EMS_ModeState::Construct);
}
