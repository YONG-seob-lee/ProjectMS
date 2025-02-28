#include "Actor/Prop/Furniture/Storage/MS_Storage.h"

#include "Manager_Client/MS_ModeManager.h"
#include "Manager_Client/MS_ScheduleManager.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "Units/MS_StorageUnit.h"
#include "Widget/Market/Storage/MS_StorageStatusWidget.h"


AMS_Storage::AMS_Storage(const FObjectInitializer& aObjectInitializer)
	: Super(aObjectInitializer)
{
}

void AMS_Storage::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AMS_Storage::BeginPlay()
{
	Super::BeginPlay();
}

void AMS_Storage::OpenStatusWidget(const FVector2D& aClickPosition)
{
	StatusWidget= gWidgetMng.Create_Widget(UMS_StorageStatusWidget::GetWidgetName(), false);

	if (StatusWidget != nullptr)
	{
		gWidgetMng.SetCustomPositionWidget(StatusWidget.Get(), aClickPosition);

		if (UMS_StorageStatusWidget* StorageStatusWidget = Cast<UMS_StorageStatusWidget>(StatusWidget))
		{
			MS_ENSURE(OwnerUnit != nullptr);
			
			if (UMS_StorageUnit* FurnitureUnit = Cast<UMS_StorageUnit>(OwnerUnit))
			{
				StorageStatusWidget->InitializeStorageDatas(FurnitureUnit->GetZoneType(), FurnitureUnit->GetTemperatureType(), FurnitureUnit->GetSlotCount());
				
				TArray<FMS_SlotData> SlotDatas;
				FurnitureUnit->GetSlotDatas(SlotDatas);
				StorageStatusWidget->UpdateSlotDatas(SlotDatas);
			
				// Widget에 Unit함수 Bind
				StorageStatusWidget->OnClickRequestSlotDelegate.BindWeakLambda(this, [this, FurnitureUnit](int32 aSlotId, int32 aItemId)
				{
					if (!IsValid(FurnitureUnit))
					{
						return;
					}

					bool bSavePlayerData = !FMS_GameDate::IsRunningTimeZone(gScheduleMng.GetDailyTimeZone());
					FurnitureUnit->SetRequestItem(aSlotId, aItemId, bSavePlayerData);
				});
			}
		}
	}
}

void AMS_Storage::OnChangeRequestSlotDatas(const TArray<FMS_SlotData>& aSlotDatas)
{
	Super::OnChangeRequestSlotDatas(aSlotDatas);

	if (StatusWidget != nullptr)
	{
		if (UMS_StorageStatusWidget* StorageStatusWidget = Cast<UMS_StorageStatusWidget>(StatusWidget))
		{
			StorageStatusWidget->UpdateSlotDatas(aSlotDatas);
		}
	}
}

void AMS_Storage::OnChangeCurrentSlotDatas(const TArray<FMS_SlotData>& aSlotDatas)
{
	Super::OnChangeCurrentSlotDatas(aSlotDatas);

	if (StatusWidget != nullptr)
	{
		if (UMS_StorageStatusWidget* StorageStatusWidget = Cast<UMS_StorageStatusWidget>(StatusWidget))
		{
			StorageStatusWidget->UpdateSlotDatas(aSlotDatas);
		}
	}
}