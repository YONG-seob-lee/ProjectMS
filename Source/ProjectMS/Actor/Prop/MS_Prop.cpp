


#include "MS_Prop.h"

#include "Component/Prop/Grid/MS_GridBoxComponent.h"
#include "Environment/MS_LevelPropDatas.h"


AMS_Prop::AMS_Prop()
	: PropType(EMS_PropType::None), TableIndex(0)
{
	PrimaryActorTick.bCanEverTick = true;

	// Component
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
}

void AMS_Prop::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// Component
	GetComponents(UMS_GridBoxComponent::StaticClass(), GridBoxComponents);
}

void AMS_Prop::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMS_Prop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

