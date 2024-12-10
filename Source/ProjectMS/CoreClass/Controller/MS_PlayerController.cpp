#include "MS_PlayerController.h"

#include "Kismet/GameplayStatics.h"
#if WITH_EDITOR
#include "LevelEditor.h"
#include "IAssetViewport.h"
#endif

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

#include "Management/MS_UnitManager.h"
#include "Management/MS_PlayerCameraManager.h"

#include "Unit/UnitState/MS_UnitStateBase.h"


AMS_PlayerController::AMS_PlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	
	PlayerCameraManagerClass = AMS_PlayerCameraManager::StaticClass();

	static ConstructorHelpers::FObjectFinder<UInputMappingContext> MAPPINGCONTEXTFINDER(TEXT("/Game/Input/MappingContext/CameraInputMappingContext"));
	MS_CHECK(MAPPINGCONTEXTFINDER.Object);

	MappingContext = MAPPINGCONTEXTFINDER.Object;

	bShowMouseCursor = true;
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

void AMS_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	RegisterManagement();

	if (UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		EnhancedInputLocalPlayerSubSystem->AddMappingContext(MappingContext, 0);
	}
}

void AMS_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

}

void AMS_PlayerController::InputTouch(const FInputActionValue& aValue)
{
	const FVector2D TouchVector = aValue.Get<FVector2D>();
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

void AMS_PlayerController::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
}

