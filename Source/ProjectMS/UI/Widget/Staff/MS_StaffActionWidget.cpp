// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_StaffActionWidget.h"

#include "Button/MS_Button.h"
#include "Components/ComboBoxString.h"
#include "ContentsUtilities/MS_AIDefine.h"
#include "Manager_Client/MS_ItemManager.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "Units/MS_StaffAIUnit.h"


void UMS_StaffActionWidget::InitWidget(const FName& aTypeName, bool bManaged, bool bAttachToRoot)
{
	Super::InitWidget(aTypeName, bManaged, bAttachToRoot);

	if(CPP_Button)
	{
		CPP_Button->GetOnClickedDelegate().AddUObject(this, &UMS_StaffActionWidget::OnClickedCancelButton);
	}
}

void UMS_StaffActionWidget::InitStaffActionWidget(TWeakObjectPtr<UMS_StaffAIUnit> aOwnerUnit)
{
	OwnerUnit = aOwnerUnit;

	InitStaffActionBox();
}

void UMS_StaffActionWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();
}

void UMS_StaffActionWidget::InitStaffActionBox()
{
	EMS_StaffUIPriorityType StaffUIPriorityType = OwnerUnit->GetPlayerStaffData().StaffUIPriorityType;
	
	if(CPP_StaffIssueBox)
	{
		CPP_StaffIssueBox->ClearOptions();
		int32 SelectedIndex = INDEX_NONE;
		
		for(int32 i = 0 ; i < static_cast<int32>(EMS_StaffUIPriorityType::EMS_StaffUIPriorityType_Max); ++i)
		{
			const FString IssueName = GetUIIssueName(i);
			CPP_StaffIssueBox->AddOption(IssueName);
			SelectItems.Emplace(i, IssueName);

			if (i == static_cast<int32>(StaffUIPriorityType))
			{
				SelectedIndex = i;
			}
		}

		CPP_StaffIssueBox->SetSelectedOption(GetUIIssueName(SelectedIndex));
		CPP_StaffIssueBox->OnSelectionChanged.AddUniqueDynamic(this, &UMS_StaffActionWidget::OnSelectChanged);
	}
}

FString UMS_StaffActionWidget::GetUIIssueName(int32 aUIIssueType) const
{
	switch(static_cast<EMS_StaffUIPriorityType>(aUIIssueType))
	{
	case EMS_StaffUIPriorityType::PaymentFirst:
		return TEXT("Payment First");
	case EMS_StaffUIPriorityType::DisplayFirst:
		return TEXT("Display First");
	case EMS_StaffUIPriorityType::ShelfFirst:
		return TEXT("Shelf First");
	case EMS_StaffUIPriorityType::PaymentOnly:
		return TEXT("Payment Only");
	case EMS_StaffUIPriorityType::DisplayOnly:
		return TEXT("Display Only");
	case EMS_StaffUIPriorityType::ShelfOnly:
		return TEXT("Shelf Only");
	default:
		return TEXT("멍때리기");
	}
}

void UMS_StaffActionWidget::OnClickedCancelButton()
{
	gWidgetMng.DestroyWidget(this);
}

void UMS_StaffActionWidget::OnSelectChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	const int32* pUIPriorityType = SelectItems.FindKey(SelectedItem);
	if(!pUIPriorityType)
	{
		return;
	}
	
	OwnerUnit->UpdateStaffPriorityOfWorks(static_cast<EMS_StaffUIPriorityType>(*pUIPriorityType));
}
