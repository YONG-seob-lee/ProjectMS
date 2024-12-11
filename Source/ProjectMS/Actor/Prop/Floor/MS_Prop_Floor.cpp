


#include "MS_Prop_Floor.h"

#include "Environment/MS_LevelPropDatas.h"


AMS_Prop_Floor::AMS_Prop_Floor()
{
	PrimaryActorTick.bCanEverTick = true;

	// Property
	PropType = EMS_PropType::Floor;
}

void AMS_Prop_Floor::BeginPlay()
{
	Super::BeginPlay();
}

void AMS_Prop_Floor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

