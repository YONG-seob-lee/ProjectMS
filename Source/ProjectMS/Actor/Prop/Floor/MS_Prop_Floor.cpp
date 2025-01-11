


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
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	if (MeshComponent)
	{
		MeshComponent->SetupAttachment(GetRootComponent());
	}

	/*
#if WITH_EDITORONLY_DATA
	WidgetComponent_ShowGridNum = CreateEditorOnlyDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent_ShowGridNum"));
	WidgetComponent_ShowGridNum->SetupAttachment(MeshComponent);
#endif
*/
}

void AMS_Prop_Floor::BeginPlay()
{
	Super::BeginPlay();
}

void AMS_Prop_Floor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMS_Prop_Floor::SetZoneData(TWeakObjectPtr<class AMS_Zone> aOwnerZone, const FVector& aPropCenterLocationInZone)
{
	Super::SetZoneData(aOwnerZone, aPropCenterLocationInZone);

	/*
#if WITH_EDITORONLY_DATA
	if (WidgetComponent_ShowGridNum)
	{
		if (UMS_EditorTextWidget* EditorTextWidget = Cast<UMS_EditorTextWidget>(WidgetComponent_ShowGridNum->GetWidget()))
		{
			FVector FZoneGridPosition = FVector((PropCenterLocationInZone - MS_GridSize / 2.f) / MS_GridSize);
			FIntVector ZoneGridPosition = FIntVector(FMath::RoundToInt32(FZoneGridPosition.X), FMath::RoundToInt32(FZoneGridPosition.Y), FMath::RoundToInt32(FZoneGridPosition.Z));
			
			if (OwnerZone != nullptr)
			{
				int32 OwnerZoneIndex = OwnerZone->GetZoneIndex();
				EditorTextWidget->SetText(FString::FromInt(OwnerZoneIndex) + FString("-") +
					FString::FromInt(ZoneGridPosition.X) + FString(",") + FString::FromInt(ZoneGridPosition.Y));
			}
		}
	}
#endif
*/
}

void AMS_Prop_Floor::SetMaterial(const FName& MaterialKey)
{
	if (Materials.Contains(MaterialKey))
	{
		MeshComponent->SetMaterial(0, *Materials.Find(MaterialKey));
	}
	else
	{
		MS_LOG_Verbosity(Error, TEXT("Material Key isn't valid"));
		
		if (Materials.Contains(FName("Normal")))
		{
			MeshComponent->SetMaterial(0, *Materials.Find(FName("Normal")));
		}
	}
}

