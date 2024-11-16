// Fill out your copyright notice in the Description page of Project Settings.


#include "MS_InputManager.h"

#include "Actor/Character/MS_CharacterBase.h"
#include "BasicClass/Controller/MS_PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Management/MS_Management.h"
#include "Utility/MS_Define.h"

void UMS_InputManager::BuiltInInitialize()
{
	Super::BuiltInInitialize();
}

void UMS_InputManager::Initialize()
{
	Super::Initialize();
}

void UMS_InputManager::PostInitialize()
{
	Super::PostInitialize();
}

void UMS_InputManager::PreFinalize()
{
	Super::PreFinalize();
}

void UMS_InputManager::Finalize()
{
	Super::Finalize();
}

void UMS_InputManager::BuiltInFinalize()
{
	Super::BuiltInFinalize();
}

void UMS_InputManager::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
}

void UMS_InputManager::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Add Input Mapping Context
	TObjectPtr<UMS_Management> Management = Cast<UMS_Management>(GetOuter());
	MS_CHECK(Management);
	TObjectPtr<AMS_PlayerController> PlayerController = Cast<AMS_PlayerController>(Management->GetOuter());
	MS_CHECK(PlayerController);

	CharacterBase = PlayerController->GetCharacterBase();
	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Move
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &UMS_InputManager::InputMove);
		
	}
}

void UMS_InputManager::InputMove(const FInputActionValue& Value)
{
	
}
