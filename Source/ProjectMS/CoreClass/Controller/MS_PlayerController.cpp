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
	
	if (UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		EnhancedInputLocalPlayerSubSystem->AddMappingContext(MappingContext, 0);
	}
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

inline FIntVector2 AMS_PlayerController::AcquireViewportSize()
{
	int ViewportSizeX = 0, ViewportSizeY = 0;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	return FIntVector2(ViewportSizeX, ViewportSizeY);
}

inline FVector2D AMS_PlayerController::AcquireMousePositionOnViewport()
{
	static FVector2D CachedRelativeCursorPosition = {};
	TSharedPtr<SWindow> ActiveTopLevelWindow = FSlateApplication::Get().GetActiveTopLevelWindow();

#if WITH_EDITOR
	TSharedPtr<IAssetViewport> GetFirstActiveViewport = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor").GetFirstActiveViewport();
#endif

	if (ActiveTopLevelWindow.IsValid() == false)
	{
		return CachedRelativeCursorPosition;
	}

	FVector2D ClientPositionErrorMargin = {};

#if WITH_EDITOR
	if (GetFirstActiveViewport->HasPlayInEditorViewport() == true)
	{
		ClientPositionErrorMargin.X = 0.0f; ClientPositionErrorMargin.Y = 0.0f;
	}
	else if (ActiveTopLevelWindow->GetWindowMode() == EWindowMode::Windowed)
	{
		ClientPositionErrorMargin.X = 0.0f; ClientPositionErrorMargin.Y = -2.0f;
	}
	else if (ActiveTopLevelWindow->GetWindowMode() == EWindowMode::WindowedFullscreen || ActiveTopLevelWindow->GetWindowMode() == EWindowMode::Fullscreen)
	{
		ClientPositionErrorMargin.X = 0.0f; ClientPositionErrorMargin.Y = 0.0f;
	}
#else
	if (ActiveTopLevelWindow->GetWindowMode() == EWindowMode::Windowed)
	{
		ClientPositionErrorMargin.X = 0.0f; ClientPositionErrorMargin.Y = -2.0f;
	}
	else if (ActiveTopLevelWindow->GetWindowMode() == EWindowMode::WindowedFullscreen || ActiveTopLevelWindow->GetWindowMode() == EWindowMode::Fullscreen)
	{
		ClientPositionErrorMargin.X = 0.0f; ClientPositionErrorMargin.Y = 0.0f;
	}
#endif

	FVector2D ClientPositionInScreen = {};

#if WITH_EDITOR
	if (GetFirstActiveViewport->HasPlayInEditorViewport() == false)
	{
		ClientPositionInScreen = FVector2D(ActiveTopLevelWindow->GetClientRectInScreen().Left, ActiveTopLevelWindow->GetClientRectInScreen().Top);
	}
	else
	{
		ClientPositionInScreen = FVector2D(FMath::CeilToFloat(GetFirstActiveViewport->AsWidget()->GetCachedGeometry().GetAbsolutePosition().X), FMath::CeilToFloat(GetFirstActiveViewport->AsWidget()->GetCachedGeometry().GetAbsolutePosition().Y));
	}

#else
	ClientPositionInScreen = FVector2D(ActiveTopLevelWindow->GetClientRectInScreen().Left, ActiveTopLevelWindow->GetClientRectInScreen().Top);
#endif
	FVector2D FixedClientPositionInScreen = ClientPositionInScreen + ClientPositionErrorMargin;
	FVector2D AbsoulteCursorPosition = FSlateApplication::Get().GetCursorPos();
	FVector2D RelativeCursorPosition = AbsoulteCursorPosition - FixedClientPositionInScreen;
	CachedRelativeCursorPosition = RelativeCursorPosition;

	return RelativeCursorPosition;
}

inline FVector2D AMS_PlayerController::AcquireTouchPositionOnViewport(ETouchIndex::Type aFingerIndex)
{
	FVector2D TouchPosition = {};
	bool CurrentlyTouchPressFlag = {};
	GetInputTouchState(aFingerIndex, TouchPosition.X, TouchPosition.Y, CurrentlyTouchPressFlag);
	return TouchPosition;
}

void AMS_PlayerController::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
}

