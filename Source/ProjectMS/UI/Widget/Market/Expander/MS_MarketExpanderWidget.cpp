// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_MarketExpanderWidget.h"

#include "MS_ConstructExpanerWidget.h"
#include "Button/MS_Button.h"


namespace ArrowAnimation
{
	const FName Open = TEXT("Open");
	const FName Close = TEXT("Close");
	const FName OpenItemList = TEXT("OpenItemList");
	const FName CloseItemList = TEXT("CloseItemList");
}

void UMS_MarketExpanderWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UMS_MarketExpanderWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	FillDefaultAnimations();

	if(CPP_ConstructExpanderWidget)
	{
		CPP_ConstructExpanderWidget->SetOnClickedCategoryButtonFunc([this](int32 ZoneType)
		{
			OpenExpander(ZoneType);
		});
		CPP_ConstructExpanderWidget->SetOnClickedConstructItemFunc([this]()
		{
			bOpen = false;
			bOpenExpander = false;
			PlayAnimationByName(ArrowAnimation::Close);
		});
	}
	
	if(CPP_ArrowButton)
	{
		CPP_ArrowButton->GetOnClickedDelegate().AddUObject(this, &UMS_MarketExpanderWidget::OnClickedArrowButton);
		CPP_ArrowButton->SetVisibility(ESlateVisibility::Visible);
	}
}

void UMS_MarketExpanderWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UMS_MarketExpanderWidget::OpenArrow(bool bOpenArrow /* = true */)
{
	if(bOpenArrow)
	{
		CPP_ConstructExpanderWidget->InitCategory();
		CPP_ConstructExpanderWidget->RefreshConstructListItems(EMS_ZoneType::Display);
		PlayAnimationByName(ArrowAnimation::Open);
		bOpen = true;	
	}
	else
	{
		if(bOpen == false)
		{
			return;
		}
		PlayAnimationByName(ArrowAnimation::Close);
		bOpen = false;
	}
}

void UMS_MarketExpanderWidget::OpenExpander(int32 ZoneType /* = 0 */)
{
	if(bOpen && bOpenExpander)
	{
		return;
	}
	
	CPP_ConstructExpanderWidget->InitCategory();
	if(static_cast<EMS_ZoneType>(ZoneType) == EMS_ZoneType::None)
	{
		CPP_ConstructExpanderWidget->RefreshConstructListItems(EMS_ZoneType::Display);
	}
	else
	{
		CPP_ConstructExpanderWidget->RefreshConstructListItems(static_cast<EMS_ZoneType>(ZoneType));
	}
	PlayAnimationByName(ArrowAnimation::OpenItemList);
	bOpen = true;
	bOpenExpander = true;
}

void UMS_MarketExpanderWidget::ResetVariable()
{
	bOpen = false;
	bOpenExpander = false;
}

void UMS_MarketExpanderWidget::OnClickedArrowButton()
{
	if(bOpen)
	{
		if(bOpenExpander)
		{
			PlayAnimationByName(ArrowAnimation::CloseItemList);
			bOpenExpander = false;
		}
		else
		{
			PlayAnimationByName(ArrowAnimation::Close);
		}
		bOpen = false;
	}
	else
	{
		PlayAnimationByName(ArrowAnimation::Open);
		bOpen = true;
	}
}
