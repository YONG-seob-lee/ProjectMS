// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_Gate.h"

#include "Character/AICharacter/MS_AICharacter.h"
#include "Components/BoxComponent.h"
#include "Manager_Client/MS_SequenceManager.h"


AMS_Gate::AMS_Gate(const FObjectInitializer& aObjectInitializer)
	: Super(aObjectInitializer), GateIndex(INDEX_NONE), LinkedGateIndex(INDEX_NONE)
{
	// Property
	PropType = EMS_PropType::Gate;

	AutoDoorTriggerBox = CreateDefaultSubobject<UBoxComponent>("AutoDoorTriggerBox");
	if(AutoDoorTriggerBox)
	{
		AutoDoorTriggerBox->AttachToComponent(SceneRootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		AutoDoorTriggerBox->SetRelativeLocation(FVector(0.f, 50.f, 100.f));
		AutoDoorTriggerBox->SetBoxExtent(FVector(100.f, 200.f, 100.f));
		AutoDoorTriggerBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &AMS_Gate::OnAutoDoorTrigger);
		AutoDoorTriggerBox->OnComponentEndOverlap.AddUniqueDynamic(this, &AMS_Gate::OnAutoDoorOutTrigger);
	}
}

void AMS_Gate::BeginPlay()
{
	Super::BeginPlay();
}

void AMS_Gate::OnAutoDoorTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(Cast<AMS_AICharacter>(OtherActor))
	{
		if(gSequenceMng.IsPlayingSequence() == false)
		{
			gSequenceMng.PlaySequence(EMS_SequenceType::OpenDoorMarket);
		}
	}
}

void AMS_Gate::OnAutoDoorOutTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(Cast<AMS_AICharacter>(OtherActor))
	{
		if(gSequenceMng.IsPlayingSequence() == false)
		{
			gSequenceMng.PlaySequence(EMS_SequenceType::CloseDoorMarket);
		}
	}
}

