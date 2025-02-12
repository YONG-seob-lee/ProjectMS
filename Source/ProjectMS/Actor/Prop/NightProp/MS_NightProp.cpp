// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_NightProp.h"

#include "Components/SpotLightComponent.h"


// Sets default values
AMS_NightProp::AMS_NightProp()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

void AMS_NightProp::TurnOnLight() const
{
	if(SpotLightComponent.IsValid())
	{
		SpotLightComponent->SetVisibility(true);
	}
}

void AMS_NightProp::TurnOffLight() const
{
	if(SpotLightComponent.IsValid())
	{
		SpotLightComponent->SetVisibility(false);
	}
}

// Called when the game starts or when spawned
void AMS_NightProp::BeginPlay()
{
	Super::BeginPlay();

	for(const auto& Component : GetComponents())
	{
		if(const TObjectPtr<UStaticMeshComponent> StaticMesh = Cast<UStaticMeshComponent>(Component))
		{
			StaticMeshComponent = StaticMesh;
		}
		if(const TObjectPtr<USpotLightComponent> SpotLight = Cast<USpotLightComponent>(Component))
		{
			SpotLightComponent = SpotLight;
		}
	}
}

// Called every frame
void AMS_NightProp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

