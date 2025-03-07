// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_Gate.h"

#include "Character/AICharacter/MS_AICharacter.h"
#include "Components/BoxComponent.h"
#include "Manager_Client/MS_SequenceManager.h"
#include "Manager_Client/MS_SoundManager.h"
#include "Zone/MS_Zone.h"


AMS_Gate::AMS_Gate(const FObjectInitializer& aObjectInitializer)
	: Super(aObjectInitializer)
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

EMS_ZoneType AMS_Gate::GetGateZoneType() const
{
	if (OwnerZone == nullptr)
	{
		MS_ENSURE(false);
	}

	return OwnerZone->GetZoneType();
}

EMS_ZoneType AMS_Gate::GetLinkedZoneType() const
{
	if (LinkedGate == nullptr)
	{
		return EMS_ZoneType::None;
	}

	return LinkedGate->GetGateZoneType();
}

void AMS_Gate::OnAutoDoorTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(bOpen)
	{
		return;
	}
	
	TArray<AActor*> OverlappingActors = {};
	AutoDoorTriggerBox->GetOverlappingActors(OverlappingActors);
	if(OverlappingActors.Num() == 1)
	{
		if(Cast<AMS_AICharacter>(OtherActor))
		{
			gSoundMng.PlaySound(EMS_SoundClassType::UserInterface, EMS_SoundWaveType::DoorBell);
			gSequenceMng.PlaySequence(EMS_SequenceType::OpenDoorMarket, FMS_SequencePlayParameter(false, false, false));
			bOpen = true;
		}	
	}
}

void AMS_Gate::OnAutoDoorOutTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(bOpen == false)
	{
		return;
	}
	TArray<AActor*> OverlappingActors = {};
	AutoDoorTriggerBox->GetOverlappingActors(OverlappingActors);
	if(OverlappingActors.Num() == 0)
	{
		if(Cast<AMS_AICharacter>(OtherActor))
		{
			gSequenceMng.PlaySequence(EMS_SequenceType::CloseDoorMarket, FMS_SequencePlayParameter(false, false, false));
			bOpen = false;
		}	
	}
}

