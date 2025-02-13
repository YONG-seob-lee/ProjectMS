#include "Actor/Prop/Furniture/Storage/MS_Storage.h"

#include "Manager_Client/MS_ModeManager.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "Units/MS_FurnitureUnit.h"
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
	if (gModeMng.GetCurrentModeStateId() == EMS_ModeState::Normal)
	{
		StatusWidget= gWidgetMng.Create_Widget(UMS_StorageStatusWidget::GetWidgetName(), false);

		if (StatusWidget != nullptr)
		{
			gWidgetMng.SetCustomPositionWidget(StatusWidget.Get(), aClickPosition);

			if (UMS_StorageStatusWidget* StorageStatusWidget = Cast<UMS_StorageStatusWidget>(StatusWidget))
			{
				MS_ENSURE(OwnerUnit != nullptr);
				
				StorageStatusWidget->SetOwnerUnit(OwnerUnit.Get());
				
				// Widget에 Unit함수 Bind
				StorageStatusWidget->OnClickShelfSlotDelegate.BindWeakLambda(this, [this](int32 aSlotId, int32 aItemId)
				{
					MS_ENSURE(OwnerUnit != nullptr);

					if (UMS_FurnitureUnit* FurnitureUnit = Cast<UMS_FurnitureUnit>(OwnerUnit))
					{
						FurnitureUnit->TakeItemsImmediately(aSlotId, aItemId);
					}
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
			StorageStatusWidget->OnChangeSlotDatas(aSlotDatas);
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
			StorageStatusWidget->OnChangeSlotDatas(aSlotDatas);
		}
	}
}