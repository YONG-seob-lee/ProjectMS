


#include "MS_Prop.h"

#include "Component/Actor/Prop/MS_PropSpaceComponent.h"
#include "Components/WidgetComponent.h"
#include "Manager_Client/MS_WidgetManager.h"
#include "Table/RowBase/MS_StorageData.h"
#include "Units/MS_StorageUnit.h"
#include "Widget/MS_Widget.h"
#include "Widget/Market/MS_ArrangementWidget.h"
#include "Zone/MS_Zone.h"


AMS_Prop::AMS_Prop(const FObjectInitializer& aObjectInitializer)
	: Super(aObjectInitializer.SetDefaultSubobjectClass<UBoxComponent>(TEXT("ShapeCollisionComponent"))
	.SetDefaultSubobjectClass<UStaticMeshComponent>(TEXT("FirstMeshComponent")))
	, PropType(EMS_PropType::None), TableIndex(0)
{
	// Component
	// Mesh Components
	UMeshComponent* FirstMeshComponent = CreateDefaultSubobject<UMeshComponent>(TEXT("FirstMeshComponent"));
	if (FirstMeshComponent)
	{
		MeshComponents.Add(FirstMeshComponent);
		FirstMeshComponent->SetupAttachment(SceneRootComponent);
		FirstMeshComponent->SetCollisionProfileName(TEXT("ClickableShape"));
	}

	// Widget Component
	ArrangementWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("ArrangementWidgetComponent"));
	if (ArrangementWidgetComponent)
	{
		ArrangementWidgetComponent->SetupAttachment(GetRootComponent());
		ArrangementWidgetComponent->SetVisibility(false);
	}
}

void AMS_Prop::PreInitializeComponents()
{
	Super::PreInitializeComponents();
	
	// Component
	GetComponents<UMS_PropSpaceComponent>(PropSpaceComponents);
}

void AMS_Prop::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	// Widget Component
	ShowArrangementWidget(false);

	// Component
	TArray<UPrimitiveComponent*> PrimitiveComponents;
	GetComponents<UPrimitiveComponent>(PrimitiveComponents);

	// Physics off
	for (UPrimitiveComponent* PrimitiveComponent : PrimitiveComponents)
	{
		PrimitiveComponent->SetSimulatePhysics(false);
		PrimitiveComponent->SetEnableGravity(false);
	}
}

void AMS_Prop::BeginPlay()
{
	Super::BeginPlay();
}

FIntVector2 AMS_Prop::GetGridPosition() const
{
	return FMS_GridData::ConvertLocationToGridPosition(GetActorLocation());
}

UMeshComponent* AMS_Prop::GetMeshComponent(int32 aArrayIndex /* = 0 */ ) const
{
	if (MeshComponents.IsValidIndex(aArrayIndex))
	{
		return MeshComponents[aArrayIndex];
	}

	return nullptr;
}

TArray<UMS_PropSpaceComponent*> AMS_Prop::GetPropPurposeSpaceComponents(EMS_PurposeType aPropPurposeSpace) const
{
	TArray<UMS_PropSpaceComponent*> Ret;

	if (aPropPurposeSpace == EMS_PurposeType::Any)
	{
		for (auto&PropSpaceComponent : PropSpaceComponents)
		{
			if (PropSpaceComponent->GetPropPurposeSpaceType() != EMS_PurposeType::None)
			{
				Ret.Emplace(PropSpaceComponent);
			}
		}
	}
	else
	{
		for (auto&PropSpaceComponent : PropSpaceComponents)
		{
			if (PropSpaceComponent->GetPropPurposeSpaceType() == aPropPurposeSpace)
			{
				Ret.Emplace(PropSpaceComponent);
			}
		}
	}
	
	return Ret;
}

UMS_PropSpaceComponent* AMS_Prop::GetPropSpaceComponentByRelativeLocation(const FVector& aRelativeLocation) const
{
	for (UMS_PropSpaceComponent* PropSpaceComponent : PropSpaceComponents)
	{
		if (PropSpaceComponent->GetRelativeLocation() == aRelativeLocation)
		{
			return PropSpaceComponent;
		}
	}

	return nullptr;
}

void AMS_Prop::GetAllGridPositions(TArray<FIntVector2>& aOutGridPositions) const
{
	if (GetPropType() != EMS_PropType::Furniture && GetPropType() != EMS_PropType::Structure)
	{
		return;
	}

	aOutGridPositions.Empty();
	
	for (UMS_PropSpaceComponent* PropSpaceComponent : PropSpaceComponents)
	{
		FIntVector2 PropSpaceStartGridPosition = FIntVector2::ZeroValue;
		FIntVector2 PropSpaceGridNum = FIntVector2::ZeroValue;
			
		PropSpaceComponent->GetGridPositions(PropSpaceStartGridPosition, PropSpaceGridNum);
		
		// Set With Grid
		for (int i = 0; i < PropSpaceGridNum.Y; ++i)
		{
			for (int j = 0; j < PropSpaceGridNum.X; ++j)
			{
				FIntVector2 GridPosition = FIntVector2(PropSpaceStartGridPosition.X + j, PropSpaceStartGridPosition.Y + i);
				
				aOutGridPositions.Emplace(GridPosition);
			}
		}
	}
}

EMS_ZoneType AMS_Prop::GetConstructableZoneType() const
{
	if (PropType == EMS_PropType::Furniture)
	{
		FMS_StorageData* FurnitureData = gTableMng.GetTableRowData<FMS_StorageData>(EMS_TableDataType::Storage, TableIndex);
		MS_ENSURE(FurnitureData != nullptr);

		return static_cast<EMS_ZoneType>(FurnitureData->ZoneType);
	}

	return EMS_ZoneType::None;
}

void AMS_Prop::SetZoneData(TWeakObjectPtr<AMS_Zone> aOwnerZone)
{
	OwnerZone = aOwnerZone;
}

void AMS_Prop::OnSelectProp(EMS_ModeState aModeState)
{
}

void AMS_Prop::OnUnselectProp(EMS_ModeState aModeState)
{
	CloseStatusWidget();
}

void AMS_Prop::OpenStatusWidget(const FVector2D& aClickPosition)
{
}

void AMS_Prop::CloseStatusWidget()
{
	if (StatusWidget != nullptr)
	{
		gWidgetMng.DestroyWidget(StatusWidget.Get());
	}
}

void AMS_Prop::InitializeWhenPreviewProp(AMS_Prop* aLinkedProp)
{
	bIsPreviewProp = true;
	
	LinkedProp = aLinkedProp;
	
	// For PostProcess
	GetComponents(UMeshComponent::StaticClass(), MeshComponents);

	for (UMeshComponent* MeshComponent : MeshComponents)
	{
		MeshComponent->SetRenderCustomDepth(true);
	}
}

UWidgetComponent* AMS_Prop::GetArrangementWidgetComponent() const
{
	if (PropType != EMS_PropType::Floor && PropType != EMS_PropType::Wall && !bIsPreviewProp)
	{
		MS_LOG_VERBOSITY(Error, TEXT("[%s] ArrangementWidget can't attach to this prop"), *MS_FUNC_STRING);
	}
	
	return ArrangementWidgetComponent;
}

UMS_ArrangementWidget* AMS_Prop::GetArrangementWidget() const
{
	if (PropType != EMS_PropType::Floor && PropType != EMS_PropType::Wall && !bIsPreviewProp)
	{
		MS_LOG_VERBOSITY(Error, TEXT("[%s] ArrangementWidget can't attach to this prop"), *MS_FUNC_STRING);
	}
	
	if (IsValid(ArrangementWidgetComponent))
	{
		if (UUserWidget* Widget = ArrangementWidgetComponent->GetWidget())
		{
			return Cast<UMS_ArrangementWidget>(Widget);
		}
	}

	return nullptr;
}

void AMS_Prop::ShowArrangementWidget(bool bShow) const
{
	if (bShow)
	{
		if (PropType != EMS_PropType::Floor && PropType != EMS_PropType::Wall && !bIsPreviewProp)
		{
			MS_LOG_VERBOSITY(Error, TEXT("[%s] ArrangementWidget can't attach to this prop"), *MS_FUNC_STRING);
		}
	}

	if (IsValid(ArrangementWidgetComponent))
	{
		ArrangementWidgetComponent->SetVisibility(bShow);
	}
}
