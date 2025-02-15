#include "MS_PlayerController.h"

#include "MS_ManagementClient.h"
#include "Test/CheatManager/MS_CheatManager.h"
#include "Test/TestServer/MS_TestServer.h"
#include "Manager_Client/MS_InputManager.h"
#include "Manager_Client/MS_PlayerCameraManager.h"
#include "Manager_Client/MS_SceneManager.h"
#include "Mode/ModeHelper/MS_LevelModeHelper.h"
#include "Table/RowBase/MS_Level.h"

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

	CheatClass = UMS_CheatManager::StaticClass();
}

void AMS_PlayerController::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	RegisterManagement();

	TestServer = MS_NewObject<UMS_TestServer>(this);
	TestServer->Initialize();
}

void AMS_PlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	BindOnLevelLoadComplete();
}

void AMS_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetupInputComponent();

	if(ManagementClient)
	{
		ManagementClient->BeginPlay();
	}
}

void AMS_PlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	DestroyModeHelper();

	MS_DeleteObject(TestServer);
	
	UnRegisterManagement();
	
	Super::EndPlay(EndPlayReason);
}

void AMS_PlayerController::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);

	ManagementClient->Tick(aDeltaTime);
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
	if(ManagementClient)
	{
		return;
	}
	
	ManagementClient = NewObject<UMS_ManagementClient>(this);
	MS_CHECK(ManagementClient);
	ManagementClient->Initialize();
	ManagementClient->PostInitialize();
}

void AMS_PlayerController::UnRegisterManagement()
{
	if(ManagementClient)
	{
		ManagementClient->Finalize();
		ManagementClient = nullptr;
	}
}

void AMS_PlayerController::BindOnLevelLoadComplete()
{
	gSceneMng.OnLevelLoadedDelegate.AddDynamic(this, &AMS_PlayerController::OnLevelLoadComplete);
}

void AMS_PlayerController::OnLevelLoadComplete()
{
	ChangeModeHelper();
}

void AMS_PlayerController::ChangeModeHelper()
{
	DestroyModeHelper();
	CreateModeHelper();
}

void AMS_PlayerController::CreateModeHelper()
{
	FMS_Level* LevelData = gSceneMng.GetCurrentLevelData();
	if (LevelData && LevelData->LevelModeHelperClass != nullptr)
	{
		LevelModeHelper = MS_NewObject<UMS_LevelModeHelper>(this, LevelData->LevelModeHelperClass);
		LevelModeHelper->Initialize();
	}
}

void AMS_PlayerController::DestroyModeHelper()
{
	if (IsValid(LevelModeHelper))
	{
		LevelModeHelper->Finalize();
		MS_DeleteObject(LevelModeHelper);
	}
}
