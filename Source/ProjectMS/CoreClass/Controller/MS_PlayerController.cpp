// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_PlayerController.h"


// Sets default values
AMS_PlayerController::AMS_PlayerController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerCameraManagerClass = AMS_PlayerController::StaticClass();
}

void AMS_PlayerController::RegisterManagement()
{
	Management = NewObject<UMS_Management>(this);
	MS_CHECK(Management);
	Management->InitManager();
}

// Called when the game starts or when spawned
void AMS_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMS_PlayerController::PostLoad()
{
	Super::PostLoad();
}

TObjectPtr<AMS_CharacterBase> AMS_PlayerController::GetCharacterBase() const
{
	MS_CHECK(UnitBase);

	return UnitBase->GetCharacterBase();
}

TObjectPtr<UMS_TableManager> AMS_PlayerController::GetTableManager() const
{
	MS_CHECK(Management);

	return Management->GetTableManager();
}

TObjectPtr<UMS_UnitManager> AMS_PlayerController::GetUnitManager() const
{
	MS_CHECK(Management);

	return Management->GetUnitManager();
}

TObjectPtr<AMS_SceneManager> AMS_PlayerController::GetSceneManager() const
{
	MS_CHECK(Management);

	return Management->GetSceneManager();
}

TObjectPtr<UMS_WidgetManager> AMS_PlayerController::GetWidgetManager() const
{
	MS_CHECK(Management);

	return Management->GetWidgetManager();
}

// Called every frame
void AMS_PlayerController::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
}

