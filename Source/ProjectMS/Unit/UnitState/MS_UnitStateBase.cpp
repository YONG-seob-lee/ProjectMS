#include "UnitState/MS_UnitStateBase.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "CoreClass/Controller/MS_PlayerController.h"

UMS_UnitStateBase::UMS_UnitStateBase() {}

void UMS_UnitStateBase::SetupPlayerInputComponent(UInputComponent* aPlayerInputComponent)
{
	MS_CHECK(PlayerController.IsValid());

	//const TObjectPtr<class UInputMappingContext> MappingContext = PlayerController->GetInputMappingContext();
	//MS_CHECK(MappingContext);

	//if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	//{
	//	Subsystem->AddMappingContext(MappingContext, 0);
	//}

	//if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(aPlayerInputComponent))
	//{
	//	// EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &UMS_PlayerUnitState::InputMove);
	//}
}

void UMS_UnitStateBase::WeakBindController(const TObjectPtr<AMS_PlayerController>& aPlayerController)
{
	PlayerController = aPlayerController;
}