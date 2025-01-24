


#include "MS_Prop.h"

#include "Component/Prop/MS_PropSpaceComponent.h"
#include "Components/WidgetComponent.h"
#include "Widget/MS_Widget.h"
#include "Widget/Market/MS_ArrangementWidget.h"
#include "Zone/MS_Zone.h"


AMS_Prop::AMS_Prop(const FObjectInitializer& aObjectInitializer)
	: Super(aObjectInitializer.SetDefaultSubobjectClass<UBoxComponent>(TEXT("ShapeCollisionComponent"))
	.SetDefaultSubobjectClass<UStaticMeshComponent>(TEXT("FirstMeshComponent")))
	, PropType(EMS_PropType::None), TableIndex(0)
{
	// Component
	// Shape Collision Component
	ShapeCollisionComponent = CreateDefaultSubobject<UPrimitiveComponent>(TEXT("ShapeCollisionComponent"));
	if (ShapeCollisionComponent)
	{
		ShapeCollisionComponent->SetupAttachment(SceneRootComponent);
		ShapeCollisionComponent->SetCollisionProfileName(TEXT("ShapeCollision"));
		
		if (UBoxComponent* Box = Cast<UBoxComponent>(ShapeCollisionComponent))
		{
			ShapeCollisionComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
			Box->SetBoxExtent(FVector(50.0f, 50.0f, 100.0f));
		}
	}

	// Mesh Components
	UMeshComponent* FirstMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FirstMeshComponent"));
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
}

void AMS_Prop::BeginPlay()
{
	Super::BeginPlay();
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

void AMS_Prop::SetZoneData(TWeakObjectPtr<AMS_Zone> aOwnerZone, const FIntVector2& aGridPosition)
{
	OwnerZone = aOwnerZone;

	GridPosition = aGridPosition;
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
		MS_LOG_Verbosity(Error, TEXT("[%s] ArrangementWidget can't attach to this prop"), *MS_FUNC_STRING);
	}
	
	return ArrangementWidgetComponent;
}

UMS_ArrangementWidget* AMS_Prop::GetArrangementWidget() const
{
	if (PropType != EMS_PropType::Floor && PropType != EMS_PropType::Wall && !bIsPreviewProp)
	{
		MS_LOG_Verbosity(Error, TEXT("[%s] ArrangementWidget can't attach to this prop"), *MS_FUNC_STRING);
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
			MS_LOG_Verbosity(Error, TEXT("[%s] ArrangementWidget can't attach to this prop"), *MS_FUNC_STRING);
		}
	}

	if (IsValid(ArrangementWidgetComponent))
	{
		ArrangementWidgetComponent->SetVisibility(bShow);
	}
}
