#include "Actor/Character/AICharacter/StaffAICharacter/MS_StaffAICharacter.h"

#include "AI/AIController/StaffAIController/MS_StaffAIController.h"
#include "ContentsUtilities/MS_ItemDefine.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "Table/Caches/MS_CommonCacheTable.h"
#include "Units/MS_StaffAIUnit.h"
#include "Widget/Staff/MS_StaffActionWidget.h"


AMS_StaffAICharacter::AMS_StaffAICharacter()
{
	AIControllerClass = AMS_StaffAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AMS_StaffAICharacter::ShowStaffStatusWidget(const FVector2D& _ClickPosition)
{
	if(UMS_Widget* Widget = gWidgetMng.Create_Widget(UMS_StaffActionWidget::GetWidgetName(), false))
	{
		if (UMS_StaffActionWidget* StaffActionWidget = Cast<UMS_StaffActionWidget>(Widget))
		{
			if (UMS_StaffAIUnit* AIUnit = Cast<UMS_StaffAIUnit>(GetOwnerUnitBase()))
			{
				StaffActionWidget->InitStaffActionWidget(AIUnit);
			}
		}
		gWidgetMng.SetCustomPositionWidget(Widget, _ClickPosition);
	}
}

void AMS_StaffAICharacter::PreInitializeComponents()
{
	Super::PreInitializeComponents();
}

void AMS_StaffAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AMS_StaffAICharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AMS_StaffAICharacter::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
}

void AMS_StaffAICharacter::OnChangeCurrentSlotDatas(const TArray<FMS_SlotData>& aSlotDatas)
{
	int32 TotalItemCount = 0;

	for (const FMS_SlotData& SlotData : aSlotDatas)
	{
		TotalItemCount += SlotData.CurrentItemCount;
	}

	if (TotalItemCount == 0)
	{
		UnEquip();
		return;
	}

	const TObjectPtr<UMS_CommonCacheTable> CommonTable = Cast<UMS_CommonCacheTable>(gTableMng.GetCacheTable(EMS_TableDataType::Common));
	MS_CHECK(CommonTable);
	
	if (TotalItemCount <= CommonTable->GetParameter01(CommonItemTableKeyName::BIGBOX_COUNT))
	{
		Equip(EquipmentName::SmallBox);
	}
	else
	{
		Equip(EquipmentName::BigBox);
	}
}
