// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_MarketStartModal.h"

#include "Button/MS_Button.h"
#include "Manager_Client/MS_ModeManager.h"
#include "Manager_Client/MS_ScheduleManager.h"
#include "Manager_Client/MS_SequenceManager.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "Widget/Market/MS_MarketWidget.h"

void UMS_MarketStartModal::NativeConstruct()
{
	Super::NativeConstruct();

	CPP_OpeningPlayButton->GetOnClickedDelegate().AddUObject(this, &UMS_MarketStartModal::OnClickedOpeningPlayButton);

	CPP_FastButton->GetOnClickedDelegate().AddWeakLambda(this, [this]()
	{
		gModeMng.ChangeState(EMS_ModeState::RunMarketNormal);
		gWidgetMng.CloseModalWidget();
	});

	
}

void UMS_MarketStartModal::OnClickedOpeningPlayButton()
{
	CPP_OpeningPlayButton->GetOnClickedDelegate().RemoveAll(this);

	gModeMng.ChangeState(EMS_ModeState::RunMarketNormal);
	gWidgetMng.CloseModalWidget([]()
	{
		gSequenceMng.PlaySequence(EMS_SequenceType::Entrance);
		if(UMS_MarketWidget* MarketWidget = Cast<UMS_MarketWidget>(gWidgetMng.GetWidget(UMS_MarketWidget::GetWidgetName())))
		{
			MarketWidget->StopRuntimeButton();
		}
	});
}
