// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_StaffDuckSpawnPoint.h"

#include "Components/ArrowComponent.h"
#include "Components/BillboardComponent.h"
#include "Components/CapsuleComponent.h"


AMS_StaffDuckSpawnPoint::AMS_StaffDuckSpawnPoint(const FObjectInitializer& ObjectInitializer)
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
			aArrowComponent->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));
		}
	}
	
	const TObjectPtr<UCapsuleComponent> Capsule = GetCapsuleComponent();
	Capsule->SetCapsuleSize(90.f, 50.f, false);
#endif
}

void AMS_StaffDuckSpawnPoint::UpdateSpawnData(FMS_PlayerStaffData* aPlayerStaffData, int32 aSpawnMinute)
{
	SpawnDatas.Emplace(aPlayerStaffData, aSpawnMinute);
}

FVector AMS_StaffDuckSpawnPoint::GetSpawnLocation()
{
	return GetActorLocation();
}

FRotator AMS_StaffDuckSpawnPoint::GetSpawnRotation()
{
	return GetActorRotation();
}

bool AMS_StaffDuckSpawnPoint::IsSpawnThisMinute(int32 aCurrentMinute, TArray<FMS_PlayerStaffData*>& aStaffData)
{
	aStaffData.Empty();
	for(const auto& SpawnData : SpawnDatas)
	{
		if(SpawnData.Value >= aCurrentMinute - 1 && SpawnData.Value <= aCurrentMinute + 1)
		{
			aStaffData.Emplace(SpawnData.Key);
		}
	}

	
	return aStaffData.IsEmpty() == false;
}

void AMS_StaffDuckSpawnPoint::BeginPlay()
{
	Super::BeginPlay();
}

void AMS_StaffDuckSpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

