#include "Actor/Prop/Furniture/Storage/MS_Storage.h"

#include "Manager_Client/MS_ModeManager.h"
#include "Manager_Client/MS_ScheduleManager.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "Units/MS_StorageUnit.h"
#include "Widget/Market/Storage/MS_StorageStatusWidget.h"
#include "Component/Actor/Item/MS_ItemSlotChildActorComponent.h"


AMS_Storage::AMS_Storage(const FObjectInitializer& aObjectInitializer)
	: Super(aObjectInitializer)
{
	FurnitureType = EMS_FurnitureType::Storage;

	
	ItemSlotAttachedComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SlotAttachedComponent"));
	if (ItemSlotAttachedComponent)
	{
		ItemSlotAttachedComponent->SetupAttachment(SceneRootComponent);
	}
}

void AMS_Storage::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	TArray<UMS_ItemSlotChildActorComponent*> SlotComponents;
	GetComponents<UMS_ItemSlotChildActorComponent>(SlotComponents);

	for (UMS_ItemSlotChildActorComponent* SlotComponent : SlotComponents)
	{
		if (SlotComponent->GetSlotId() == INDEX_NONE)
		{
			MS_LOG_VERBOSITY(Error, TEXT("[%s] Please set slot components order"), *MS_FUNC_STRING);
			MS_ENSURE(false);
		}
		
		ItemSlotIdToSlotComponents.Emplace(SlotComponent->GetSlotId(), SlotComponent);
	}
}

void AMS_Storage::BeginPlay()
{
	Super::BeginPlay();
}

TWeakObjectPtr<class UMS_Widget> AMS_Storage::OpenStatusWidget()
{
	StatusWidget= gWidgetMng.Create_Widget(UMS_StorageStatusWidget::GetWidgetName(), false);

	if (StatusWidget != nullptr)
	{
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

		return StatusWidget;
	}

	return nullptr;
}

void AMS_Storage::OnChangeRequestSlotDatas(const TArray<FMS_SlotData>& aSlotDatas)
{
	for (auto& It : ItemSlotIdToSlotComponents)
	{
		if (aSlotDatas.IsValidIndex(It.Key))
		{
			It.Value->OnChangeRequestSlotData(aSlotDatas[It.Key]);
		}
		else
		{
			It.Value->OnChangeRequestSlotData(FMS_SlotData());
		}
	}

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
	for (auto& It : ItemSlotIdToSlotComponents)
	{
		if (aSlotDatas.IsValidIndex(It.Key))
		{
			It.Value->OnChangeCurrentSlotData(aSlotDatas[It.Key]);
		}
		else
		{
			It.Value->OnChangeCurrentSlotData(FMS_SlotData());
		}
	}
	
	if (StatusWidget != nullptr)
	{
		if (UMS_StorageStatusWidget* StorageStatusWidget = Cast<UMS_StorageStatusWidget>(StatusWidget))
		{
			StorageStatusWidget->UpdateSlotDatas(aSlotDatas);
		}
	}
}