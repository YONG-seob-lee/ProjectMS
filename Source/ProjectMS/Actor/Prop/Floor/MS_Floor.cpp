


#include "MS_Floor.h"

#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Level/MS_LevelDefine.h"
#include "Widget/Editor/MS_EditorTextWidget.h"
#include "Zone/MS_Zone.h"


AMS_Floor::AMS_Floor(const FObjectInitializer& aObjectInitializer)
	: Super(aObjectInitializer)
{
	// Property
	PropType = EMS_PropType::Floor;

	// Component
	if (UBoxComponent* Box = Cast<UBoxComponent>(ShapeCollisionComponent))
	{
		ShapeCollisionComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		Box->SetBoxExtent(FVector(25.0f, 25.0f, 0.0f));
	}
	
/*#if WITH_EDITORONLY_DATA
	if (MeshComponents.IsValidIndex(0))
	{
		WidgetComponent_ShowGridNum = CreateEditorOnlyDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent_ShowGridNum"));
		WidgetComponent_ShowGridNum->SetupAttachment(MeshComponents[0]);
	}
#endif*/
}

void AMS_Floor::BeginPlay()
{
	Super::BeginPlay();

	/*#if WITH_EDITORONLY_DATA
	if (WidgetComponent_ShowGridNum)
	{
		if (UMS_EditorTextWidget* EditorTextWidget = Cast<UMS_EditorTextWidget>(WidgetComponent_ShowGridNum->GetWidget()))
		{
			EditorTextWidget->SetText(FString::FromInt(GridPosition.X) + FString(",") + FString::FromInt(GridPosition.Y));
		}
	}
#endif*/
}

void AMS_Floor::SetMaterial(const FName& MaterialKey)
{
	for (UMeshComponent* MeshComponent : MeshComponents)
	{
		if (Materials.Contains(MaterialKey))
		{
			MeshComponent->SetMaterial(0, *Materials.Find(MaterialKey));
		}
		else
		{
			MS_LOG_VERBOSITY(Error, TEXT("Material Key isn't valid"));
		
			if (Materials.Contains(FName("Normal")))
			{
				MeshComponent->SetMaterial(0, *Materials.Find(FName("Normal")));
			}
		}
	}
}

