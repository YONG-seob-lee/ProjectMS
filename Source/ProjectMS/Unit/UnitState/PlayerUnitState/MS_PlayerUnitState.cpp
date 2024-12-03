#include "Unit/UnitState/PlayerUnitState/MS_PlayerUnitState.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "CoreClass/Controller/MS_PlayerController.h"
#include "Unit/UnitInputHandler/MS_UnitInputHandler.h"

UMS_PlayerUnitState::UMS_PlayerUnitState()
{
	UnitInputHandler = CreateDefaultSubobject<UMS_UnitInputHandler>(TEXT("UnitInputHandler"));
}

void UMS_PlayerUnitState::WeakBindController(const TObjectPtr<class AMS_PlayerController>& aPlayerController)
{
	Super::WeakBindController(aPlayerController);

	MS_CHECK(aPlayerController->InputComponent);

	UnitInputHandler->BindController(aPlayerController);
}
