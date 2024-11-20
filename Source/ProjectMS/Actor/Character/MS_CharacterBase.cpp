// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_CharacterBase.h"

#include "Unit/MS_UnitBase.h"
#include "Unit/Public/UnitState/MS_UnitStateBase.h"


// Sets default values
AMS_CharacterBase::AMS_CharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMS_CharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMS_CharacterBase::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
}

// Called to bind functionality to input
void AMS_CharacterBase::SetupPlayerInputComponent(UInputComponent* aPlayerInputComponent)
{
	Super::SetupPlayerInputComponent(aPlayerInputComponent);

	const TObjectPtr<UMS_UnitBase> Unit = Cast<UMS_UnitBase>(GetOuter());
	MS_CHECK(Unit);

	const TObjectPtr<UMS_UnitStateBase> UnitStateBase = Cast<UMS_UnitStateBase>(Unit->GetCurrentUnitState());
	MS_CHECK(UnitStateBase);

	UnitStateBase->SetupPlayerInputComponent(aPlayerInputComponent);
}

void AMS_CharacterBase::SetLodScaleValues(float aCullDistanceScale, float aOutLineCullDistanceScale, bool bVisibleOutLine)
{
	LodValues.CullDistanceScale = aCullDistanceScale;
	LodValues.OutLineCullDistanceScale = aOutLineCullDistanceScale;
	LodValues.bVisibleOutLine = bVisibleOutLine;
}

