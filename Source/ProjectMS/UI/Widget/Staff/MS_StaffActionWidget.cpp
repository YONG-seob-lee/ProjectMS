// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_StaffActionWidget.h"

#include "Button/MS_Button.h"
#include "Components/ComboBoxString.h"
#include "ContentsUtilities/MS_AIDefine.h"
#include "Manager_Client/MS_WidgetManager.h"

void UMS_StaffActionWidget::InitWidget(const FName& aTypeName, bool bManaged, bool bAttachToRoot)
{
	Super::InitWidget(aTypeName, bManaged, bAttachToRoot);

	InitStaffActionBox();

	if(CPP_Button)
	{
		CPP_Button->GetOnClickedDelegate().AddUObject(this, &UMS_StaffActionWidget::OnClickedCancelButton);
	}
}

void UMS_StaffActionWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();
}

void UMS_StaffActionWidget::InitStaffActionBox()
{
	if(CPP_StaffIssueBox)
	{
		for(int32 i = static_cast<int32>(EMS_StaffIssueType::None) ; i < static_cast<int32>(EMS_StaffIssueType::AddItemsToShelf); i++)
		{
			const FString IssueName = GetIssueName(i);
			CPP_StaffIssueBox->AddOption(IssueName);
			SelectItems.Emplace(i, IssueName);
		}

		CPP_StaffIssueBox->OnSelectionChanged.AddUniqueDynamic(this, &UMS_StaffActionWidget::OnSelectChanged);
	}

	// 최초 Staff의 이슈 넣기
	const EMS_StaffIssueType CurrentIssueType = EMS_StaffIssueType::None;
	CPP_StaffIssueBox->SetSelectedOption(GetIssueName(static_cast<int32>(CurrentIssueType)));
}

FString UMS_StaffActionWidget::GetIssueName(int32 _IssueType)
{
	switch(static_cast<EMS_StaffIssueType>(_IssueType))
	{
	case EMS_StaffIssueType::Payment:
		return TEXT("Payment");
	case EMS_StaffIssueType::RemoveItemsFromDisplay:
	case EMS_StaffIssueType::AddItemsToDisplay:
		return TEXT("Store Display");
	case EMS_StaffIssueType::RemoveItemsFromShelf:
		return TEXT("Return Item");
	case EMS_StaffIssueType::AddItemsToShelf:
		return TEXT("Shelf Loading");
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
	const int32* StaffIssueType = SelectItems.FindKey(SelectedItem);
	
	if(!StaffIssueType)
	{
		return;
	}

	const EMS_StaffIssueType IssueType = static_cast<EMS_StaffIssueType>(*StaffIssueType);
	// 타입 변경하기.
}
