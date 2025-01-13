// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_StorageSlotManagementWidget.h"

#include "MS_SlotWidget.h"
#include "Components/Image.h"

void UMS_StorageSlotManagementWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(CPP_Slot01)
	{
		CPP_Slot01->SetVisibility(ESlateVisibility::Visible);
	}
	if(CPP_Slot02)
	{
		CPP_Slot02->SetVisibility(ESlateVisibility::Visible);
	}
	if(CPP_Slot03)
	{
		CPP_Slot03->SetVisibility(ESlateVisibility::Visible);
	}
	if(CPP_Slot04)
	{
		CPP_Slot04->SetVisibility(ESlateVisibility::Visible);
	}
}

void UMS_StorageSlotManagementWidget::NativeDestruct()
{
	Super::NativeDestruct();
}
