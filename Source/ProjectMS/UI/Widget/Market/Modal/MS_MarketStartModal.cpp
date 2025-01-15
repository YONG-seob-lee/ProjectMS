// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_MarketStartModal.h"

#include "Button/MS_Button.h"
#include "Manager_Client/MS_ScheduleManager.h"
#include "Manager_Client/MS_WidgetManager.h"

void UMS_MarketStartModal::NativeConstruct()
{
	Super::NativeConstruct();

	CPP_OpeningPlayButton->GetOnClickedDelegate().AddUObject(this, &UMS_MarketStartModal::OnClickedOpeningPlayButton);

	CPP_FastButton->GetOnClickedDelegate().AddWeakLambda(this, [this]()
	{
		if(Test)
		{
			gScheduleMng.SetTest();
			Test();
		}
	});
}

void UMS_MarketStartModal::OnClickedOpeningPlayButton()
{
	CPP_OpeningPlayButton->GetOnClickedDelegate().RemoveAll(this);

	gWidgetMng.CloseModalWidget();
}
