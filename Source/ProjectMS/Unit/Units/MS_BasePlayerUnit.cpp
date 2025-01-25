// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_BasePlayerUnit.h"

#include "Character/MS_CharacterBase.h"
#include "CoreClass/Controller/MS_PlayerController.h"


void UMS_BasePlayerUnit::Initialize(MS_Handle aUnitHandle, int32 aUnitTableId, int32 aChildTableId)
{
	Super::Initialize(aUnitHandle, aUnitTableId, aChildTableId);
}

void UMS_BasePlayerUnit::Finalize()
{
	Super::Finalize();
}

void UMS_BasePlayerUnit::PostInitialize()
{
	Super::PostInitialize();
}

void UMS_BasePlayerUnit::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
}

bool UMS_BasePlayerUnit::CreateUnitActor(const FVector& aPosition, const FRotator& aRotator)
{
	// 예외적으로 Table을 통하지 않고 Class를 직접 지정하여 사용
	if (Super::Super::CreateUnitActor(aPosition, aRotator))
	{
		if(const TObjectPtr<AMS_CharacterBase> NewCharacter = CreateCharacter(AMS_CharacterBase::StaticClass(), aPosition, aRotator))
		{
			NewCharacter->SetOwnerUnitBase(this);
		
			return true;
		}
	}

	MS_ENSURE(false);
	return false;
}

void UMS_BasePlayerUnit::DestroyUnitActor()
{
	Super::DestroyUnitActor();
}

void UMS_BasePlayerUnit::SetLodScaleValues(float aCullDistanceScale, float aOutLineCullDistanceScale, bool bVisibleOutLine) const
{
	if(GetCharacter())
	{
		GetCharacter()->SetLodScaleValues(aCullDistanceScale, aOutLineCullDistanceScale, bVisibleOutLine);
	}
}

void UMS_BasePlayerUnit::ChangeState(EMS_UnitState aActionType) const
{
	if(APlayerController* PlayerController = Cast<APlayerController>(GetCharacter()->GetController()))
	{
		PlayerController->FlushPressedKeys();
	}
	
	Super::ChangeState(aActionType);
}
