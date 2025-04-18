#include "Actor/Prop/Furniture/Counter/MS_Counter.h"


AMS_Counter::AMS_Counter(const FObjectInitializer& aObjectInitializer)
	: Super(aObjectInitializer)
{
	FurnitureType = EMS_FurnitureType::Counter;
}

void AMS_Counter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AMS_Counter::BeginPlay()
{
	Super::BeginPlay();
}
