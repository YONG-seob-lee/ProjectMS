


#include "MS_Prop_Floor.h"

#include "Components/WidgetComponent.h"
#include "Environment/MS_LevelPropDatas.h"
#include "Widget/Editor/MS_EditorTextWidget.h"
#include "Zone/MS_Zone.h"


AMS_Prop_Floor::AMS_Prop_Floor()
{
	PrimaryActorTick.bCanEverTick = true;

	// Property
	PropType = EMS_PropType::Floor;

	// Component
#if WITH_EDITORONLY_DATA
	WidgetComponent_ShowGridNum = CreateEditorOnlyDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent_ShowGridNum"));
	WidgetComponent_ShowGridNum->SetupAttachment(MeshComponent);
#endif
}

void AMS_Prop_Floor::BeginPlay()
{
	Super::BeginPlay();
}

void AMS_Prop_Floor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMS_Prop_Floor::SetZoneData(TWeakObjectPtr<AMS_Zone> aOwnerZone, const FIntVector2& aZoneGridPosition)
{
	Super::SetZoneData(aOwnerZone, aZoneGridPosition);

#if WITH_EDITORONLY_DATA
	if (WidgetComponent_ShowGridNum)
	{
		if (UMS_EditorTextWidget* EditorTextWidget = Cast<UMS_EditorTextWidget>(WidgetComponent_ShowGridNum->GetWidget()))
		{
			if (OwnerZone != nullptr)
			{
				int32 OwnerZoneIndex = OwnerZone->GetZoneIndex();
				EditorTextWidget->SetText(FString::FromInt(OwnerZoneIndex) + FString(" - ") +
					FString::FromInt(ZoneGridPosition.X) + FString(" , ") + FString::FromInt(ZoneGridPosition.Y));
			}
		}
	}
#endif
}

