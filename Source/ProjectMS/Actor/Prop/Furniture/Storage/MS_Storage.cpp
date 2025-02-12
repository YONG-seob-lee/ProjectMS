#include "Actor/Prop/Furniture/Storage/MS_Storage.h"

#include "Manager_Client/MS_WidgetManager.h"
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

void AMS_Storage::OpenManagementWidget(const FVector2D& aClickPosition, EMS_ModeState aModeState)
{
	if (aModeState == EMS_ModeState::Normal)
	{
		gWidgetMng.SetCustomPositionWidget(gWidgetMng.Create_Widget(UMS_StorageStatusWidget::GetWidgetName(), false), aClickPosition);
	}
}

void AMS_Storage::CloseManagementWidget(EMS_ModeState aModeState)
{
	if (aModeState == EMS_ModeState::Normal)
	{
		
	}
}