// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_BasePlayer.h"

#include "BasicClass/Controller/MS_PlayerController.h"

void UMS_BasePlayer::Initialize()
{
	Super::Initialize();
}

void UMS_BasePlayer::Finalize()
{
	Super::Finalize();
}

void UMS_BasePlayer::PostInitialize()
{
	Super::PostInitialize();
}

void UMS_BasePlayer::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
}

bool UMS_BasePlayer::CreateUnit(int32 aUnitTableId, const FVector& aPos, const FRotator& aRot)
{
	return Super::CreateUnit(aUnitTableId, aPos, aRot);
}

void UMS_BasePlayer::DestroyUnit()
{
	Super::DestroyUnit();
}

void UMS_BasePlayer::ChangeActionState(EMS_UnitActionState aActionType) const
{
	if(APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		PlayerController->FlushPressedKeys();
	}
	
	Super::ChangeActionState(aActionType);
}
