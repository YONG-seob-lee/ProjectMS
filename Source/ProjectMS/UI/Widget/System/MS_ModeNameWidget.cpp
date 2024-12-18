// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_ModeNameWidget.h"

#include "Components/TextBlock.h"
#include "Manager_Both/MS_ModeManager.h"

void UMS_ModeNameWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetModeName(TEXT("Normal"));
	
	gModeMng.OnChangeModeDelegate.AddUObject(this, &UMS_ModeNameWidget::OnChangeMode);
}

void UMS_ModeNameWidget::NativeDestruct()
{
	gModeMng.OnChangeModeDelegate.RemoveAll(this);
	Super::NativeDestruct();
}

void UMS_ModeNameWidget::OnChangeMode(EMS_ModeState aModeState, EMS_ControllerModeType aControllerModeType)
{
	FString ModeStateName;
	FString ControllerModeName;
	
	switch(aModeState)
	{
	case EMS_ModeState::None:
		{
			ModeStateName = FString("None");
			break;
		}
	case EMS_ModeState::Construct:
		{
			ModeStateName = FString("Construct");
			break;
		}
	case EMS_ModeState::StaffManagement:
		{
			ModeStateName = FString("Staff");
			break;
		}
	case(EMS_ModeState::CustomerManagement):
		{
			ModeStateName = FString("Customer");
			break;		
		}
	default:
		{
			ModeStateName = FString("Error");
			break;
		}
	}

	switch(aControllerModeType)
	{
	case EMS_ControllerModeType::Normal:
		{
			ControllerModeName = FString("Normal");
			break;
		}
	case EMS_ControllerModeType::Rotate:
		{
			ControllerModeName = FString("Rotate");
			break;
		}
	}
	
	SetModeName(ModeStateName + " | " + ControllerModeName);
}

void UMS_ModeNameWidget::SetModeName(const FString& aModeName) const
{
	if(CPP_ModeText)
	{
		CPP_ModeText->SetText(FText::FromString(aModeName));
	}
}
