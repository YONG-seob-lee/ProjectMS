#include "MS_PlayerController.h"

#if WITH_EDITOR
#include "LevelEditor.h"
#endif

#include "MS_InputManager.h"
#include "Management/MS_UnitManager.h"
#include "Management/MS_PlayerCameraManager.h"

AMS_PlayerController::AMS_PlayerController()
{
	PlayerCameraManagerClass = AMS_PlayerCameraManager::StaticClass();

	PrimaryActorTick.bCanEverTick = true;
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	bEnableMouseOverEvents = true;
	bEnableTouchOverEvents = true;
}

void AMS_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	RegisterManagement();

	SetupInputComponent();
}

void AMS_PlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AMS_PlayerController::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
}

void AMS_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if(Management)
	{
		gInputMng.SetupInputComponent(InputComponent, GetLocalPlayer());
	}
}

void AMS_PlayerController::RegisterManagement()
{
	// BeginPlay
	if(Management)
	{
		return;
	}
	
	Management = NewObject<UMS_Management>(this);
	MS_CHECK(Management);
	Management->InitManager();
}