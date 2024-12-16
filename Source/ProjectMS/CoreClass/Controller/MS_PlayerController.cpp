#include "MS_PlayerController.h"

#include "MS_ManagementClient.h"
#include "Manager_Client/MS_InputManager.h"
#include "Manager_Client/MS_PlayerCameraManager.h"

#if WITH_EDITOR
#include "LevelEditor.h"
#endif


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

void AMS_PlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	RegisterManagement();
}

void AMS_PlayerController::BeginPlay()
{
	Super::BeginPlay();

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
	
	if(ManagementClient)
	{
		gInputMng.SetupInputComponent(InputComponent, GetLocalPlayer());
	}
}

void AMS_PlayerController::RegisterManagement()
{
	// BeginPlay
	if(ManagementClient)
	{
		return;
	}
	
	ManagementClient = NewObject<UMS_ManagementClient>(this);
	MS_CHECK(ManagementClient);
	ManagementClient->Initialize();
}