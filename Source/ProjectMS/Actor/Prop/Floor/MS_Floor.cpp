


#include "MS_Floor.h"

#include "Components/WidgetComponent.h"
#include "Environment/MS_LevelPropDatas.h"
#include "Widget/Editor/MS_EditorTextWidget.h"
#include "Zone/MS_Zone.h"


AMS_Floor::AMS_Floor(const FObjectInitializer& aObjectInitializer)
	: Super(aObjectInitializer)
{
	// Property
	PropType = EMS_PropType::Floor;

	// Component
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	if (MeshComponent)
	{
		MeshComponent->SetupAttachment(GetRootComponent());
	}

	
#if WITH_EDITORONLY_DATA
	WidgetComponent_ShowGridNum = CreateEditorOnlyDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent_ShowGridNum"));
	WidgetComponent_ShowGridNum->SetupAttachment(MeshComponent);
#endif

}

void AMS_Floor::BeginPlay()
{
	Super::BeginPlay();
}

void AMS_Floor::SetZoneData(TWeakObjectPtr<class AMS_Zone> aOwnerZone, const FIntVector2& aGridPosition)
{
	Super::SetZoneData(aOwnerZone, aGridPosition);

	
#if WITH_EDITORONLY_DATA
	if (WidgetComponent_ShowGridNum)
	{
		if (UMS_EditorTextWidget* EditorTextWidget = Cast<UMS_EditorTextWidget>(WidgetComponent_ShowGridNum->GetWidget()))
		{
			if (OwnerZone != nullptr)
			{
				int32 OwnerZoneIndex = OwnerZone->GetZoneIndex();
				EditorTextWidget->SetText(FString::FromInt(OwnerZoneIndex) + FString("-") +
					FString::FromInt(aGridPosition.X) + FString(",") + FString::FromInt(aGridPosition.Y));
			}
		}
	}
#endif

}

void AMS_Floor::SetMaterial(const FName& MaterialKey)
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

