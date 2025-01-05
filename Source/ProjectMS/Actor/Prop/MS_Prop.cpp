


#include "MS_Prop.h"

#include "Component/Prop/MS_PropSpaceComponent.h"
#include "Environment/MS_LevelPropDatas.h"
#include "Zone/MS_Zone.h"


AMS_Prop::AMS_Prop()
	: PropType(EMS_PropType::None), TableIndex(0)
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMS_Prop::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// Component
	GetComponents(UMS_PropSpaceComponent::StaticClass(), PropSpaceComponents);
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
	LinkedProp = aLinkedProp;
}

