// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreClass/Controller/MS_PlayerController.h"
#include "CoreClass/StateMachine/MS_StateBase.h"
#include "MS_UnitStateBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_UnitStateBase : public UMS_StateBase
{
	GENERATED_BODY()
public:
	virtual void SetupPlayerInputComponent(class UInputComponent* aPlayerInputComponent);
	void WeakBindController(const TObjectPtr<AMS_PlayerController>& aPlayerController);

private:
	// -- Move-- //
	void InputMove(const struct FInputActionValue& Value);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ITTInput, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	
	// -- Move-- //
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ITTInput, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;
	
	UPROPERTY()
	TWeakObjectPtr<class AMS_PlayerController> PlayerController = nullptr;
};
