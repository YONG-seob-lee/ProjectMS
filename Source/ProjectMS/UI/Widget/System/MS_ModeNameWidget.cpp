// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ModeNameWidget.h"

#include "MS_ModeManager.h"
#include "Components/TextBlock.h"

void UMS_ModeNameWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetModeName(TEXT("Normal"));
	
	gModeMng.OnSetMode.AddUObject(this, &UMS_ModeNameWidget::OnSetMode);
}

void UMS_ModeNameWidget::OnSetMode(uint8 aModeType)
{
	switch(static_cast<EMS_ModeType>(aModeType))
	{
		case(EMS_ModeType::Normal):
		{
			SetModeName(TEXT("Normal"));
			break;
		}
		case(EMS_ModeType::Rotate):
		{
			SetModeName(TEXT("Rotate"));
			break;
		}
		case(EMS_ModeType::Construct):
		{
			SetModeName(TEXT("Construct"));
			break;
		}
		case(EMS_ModeType::StaffManagement):
		{
			SetModeName(TEXT("Staff"));	
			break;
		}
		case(EMS_ModeType::CustomerManagement):
		{
			SetModeName(TEXT("Customer"));
			break;		
		}
		default:
		{
			break;
		}
	}
}

void UMS_ModeNameWidget::SetModeName(const FString& aModeName) const
{
	if(CPP_ModeText)
	{
		CPP_ModeText->SetText(FText::FromString(aModeName));
	}
}
