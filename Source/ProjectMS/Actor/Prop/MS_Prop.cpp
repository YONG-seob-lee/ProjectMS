


#include "MS_Prop.h"

#include "Component/Prop/MS_PropSpaceComponent.h"
#include "Components/WidgetComponent.h"
#include "Environment/MS_LevelPropDatas.h"
#include "Widget/MS_Widget.h"
#include "Widget/Market/MS_PreviewWidget.h"
#include "Zone/MS_Zone.h"


AMS_Prop::AMS_Prop()
	: PropType(EMS_PropType::None), TableIndex(0)
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRootComponent"));
	if (SceneRootComponent)
	{
		SetRootComponent(SceneRootComponent);
	}

	PreviewWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("PreviewWidgetComponent"));
	if (PreviewWidgetComponent)
	{
		PreviewWidgetComponent->SetupAttachment(GetRootComponent());
	}
}

void AMS_Prop::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// Component
	GetComponents(UMS_PropSpaceComponent::StaticClass(), PropSpaceComponents);

	if (PreviewWidgetComponent)
	{
		PreviewWidgetComponent->SetVisibility(false);
	}
}

void AMS_Prop::BeginPlay()
{
	Super::BeginPlay();
}

void AMS_Prop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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

void AMS_Prop::SetZoneData(TWeakObjectPtr<AMS_Zone> aOwnerZone, const FVector& aPropCenterLocationInZone)
{
	OwnerZone = aOwnerZone;

	PropCenterLocationInZone = aPropCenterLocationInZone;
}

void AMS_Prop::InitializeWhenPreviewProp(AMS_Prop* aLinkedProp)
{
	bIsPreviewProp = true;
	
	LinkedProp = aLinkedProp;

	// For PostProcess
	TArray<UMeshComponent*> MeshComponents;
	GetComponents(UMeshComponent::StaticClass(), MeshComponents);

	for (UMeshComponent* MeshComponent : MeshComponents)
	{
		MeshComponent->SetRenderCustomDepth(true);
	}
}

UMS_PreviewWidget* AMS_Prop::GetPreviewWidget() const
{
	if (IsValid(PreviewWidgetComponent))
	{
		if (UUserWidget* Widget = PreviewWidgetComponent->GetWidget())
		{
			return Cast<UMS_PreviewWidget>(Widget);
		}
	}

	return nullptr;
}
