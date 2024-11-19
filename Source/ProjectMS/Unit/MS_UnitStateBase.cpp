// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_UnitStateBase.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

void UMS_UnitStateBase::SetupPlayerInputComponent(UInputComponent* aPlayerInputComponent)
{
	// Add Input Mapping Context
	MS_CHECK(PlayerController.IsValid());

	const TObjectPtr<AMS_CharacterBase> CharacterBase = PlayerController->GetCharacterBase();
	MS_CHECK(CharacterBase);

	const TObjectPtr<class UInputMappingContext> MappingContext = CharacterBase->GetInputMappingContext();
	MS_CHECK(MappingContext);
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(MappingContext, 0);
	}
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(aPlayerInputComponent))
	{
		// Move
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &UMS_UnitStateBase::InputMove);
	}
}

void UMS_UnitStateBase::WeakBindController(const TObjectPtr<AMS_PlayerController>& aPlayerController)
{
	PlayerController = aPlayerController;
}

void UMS_UnitStateBase::InputMove(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	
	MS_LOG(TEXT("%s"), *MovementVector.ToString());
}
