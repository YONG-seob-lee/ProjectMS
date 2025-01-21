// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_BasePlayerUnit.h"

#include "Character/MS_CharacterBase.h"
#include "CoreClass/Controller/MS_PlayerController.h"


void UMS_BasePlayerUnit::Initialize(MS_Handle aUnitHandle)
{
	Super::Initialize(aUnitHandle);
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

bool UMS_BasePlayerUnit::CreateUnit(int32 aUnitTableId, int32 aChildTableId, const FVector& aPosition, const FRotator& aRotator)
{
	Super::CreateUnit(aUnitTableId, aChildTableId, aPosition, aRotator);
	
	// 예외적으로 Table을 통하지 않고 Class를 직접 지정하여 사용
	if(const TObjectPtr<AMS_CharacterBase> NewCharacter = CreateCharacter(AMS_CharacterBase::StaticClass(), aPosition, aRotator))
	{
		NewCharacter->SetOwnerUnitBase(this);
	
		// if(const TObjectPtr<UMS_AnimInstance> AnimInstance = Cast<UMS_AnimInstance>(GetAnimInstance()))
		// {
		// 	AnimInstance->InitializeAnimation();
		// }
		return true;
	}
	
	return false;
}

void UMS_BasePlayerUnit::DestroyUnit()
{
	Super::DestroyUnit();
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
