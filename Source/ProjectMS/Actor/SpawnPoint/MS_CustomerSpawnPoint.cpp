// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_CustomerSpawnPoint.h"

#include "Components/ArrowComponent.h"
#include "Components/BillboardComponent.h"
#include "Components/CapsuleComponent.h"


AMS_CustomerSpawnPoint::AMS_CustomerSpawnPoint(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

#if WITH_EDITORONLY_DATA
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UTexture2D> TextureFinder;
		FName Id_SpawnNpcActor;
		FText Name_SpawnNpcActor;
		
		FConstructorStatics() :	TextureFinder(TEXT("/Game/UI/Image/Portrait/DuckPortrait_White.DuckPortrait_White")),
								 Id_SpawnNpcActor(TEXT("Outside Duck AI")),
								Name_SpawnNpcActor(NSLOCTEXT("SpriteCategory", "DefaultImage", "DefaultImage")) {}
	};
	
	if (!IsRunningCommandlet())
	{
		if (const TObjectPtr<UBillboardComponent> aSpriteComponent = GetGoodSprite())
		{
			FConstructorStatics ConstructorStatics;
			aSpriteComponent->Sprite = ConstructorStatics.TextureFinder.Get();
			aSpriteComponent->EditorScale = 5.f;
			aSpriteComponent->SpriteInfo.Category = ConstructorStatics.Id_SpawnNpcActor;
			aSpriteComponent->SpriteInfo.DisplayName = ConstructorStatics.Name_SpawnNpcActor;
		}

		if (const TObjectPtr<UArrowComponent> aArrowComponent = GetArrowComponent())
		{
			aArrowComponent->ArrowSize = 2.f;
		}
	}
	
	const TObjectPtr<UCapsuleComponent> Capsule = GetCapsuleComponent();
	Capsule->SetCapsuleSize(90.f, 50.f, false);
#endif
}

FVector AMS_CustomerSpawnPoint::GetSpawnLocation()
{
	return GetActorLocation();
}

FRotator AMS_CustomerSpawnPoint::GetSpawnRotation()
{
	return GetActorRotation();
}

void AMS_CustomerSpawnPoint::BeginPlay()
{
	Super::BeginPlay();
}

void AMS_CustomerSpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

