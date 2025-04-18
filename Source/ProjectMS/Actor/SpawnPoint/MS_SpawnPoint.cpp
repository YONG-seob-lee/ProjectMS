﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_SpawnPoint.h"

#include "Components/ArrowComponent.h"
#include "Components/BillboardComponent.h"
#include "Components/CapsuleComponent.h"


AMS_SpawnPoint::AMS_SpawnPoint(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	
#if WITH_EDITORONLY_DATA
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UTexture2D> TextureFinder;
		FName Id_SpawnNpcActor;
		FText Name_SpawnNpcActor;

		FConstructorStatics() :	TextureFinder(*SpawnImage::PlayerPath),
 								Id_SpawnNpcActor(SpawnImage::PlayerName),
								Name_SpawnNpcActor(NSLOCTEXT("SpriteCategory", "DefaultImage", "DefaultImage")) {}
	};
	
	if (!IsRunningCommandlet())
	{
		if (const TObjectPtr<UBillboardComponent> aSpriteComponent = GetGoodSprite())
		{
			FConstructorStatics ConstructorStatics;
			aSpriteComponent->Sprite = ConstructorStatics.TextureFinder.Get();
			aSpriteComponent->SpriteInfo.Category = ConstructorStatics.Id_SpawnNpcActor;
			aSpriteComponent->SpriteInfo.DisplayName = ConstructorStatics.Name_SpawnNpcActor;
		}

		if (const TObjectPtr<UArrowComponent> aArrowComponent = GetArrowComponent())
		{
			aArrowComponent->ArrowSize = 1.5f;
		}
	}
	
	const TObjectPtr<UCapsuleComponent> Capsule = GetCapsuleComponent();
	Capsule->SetCapsuleSize(20.f, 40.f, false);
#endif

}

void AMS_SpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMS_SpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

