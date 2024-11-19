// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MS_CharacterBase.generated.h"

UCLASS()
class PROJECTMS_API AMS_CharacterBase : public ACharacter
{
	GENERATED_BODY()
public:
	AMS_CharacterBase();

	virtual void BeginPlay() override;
	virtual void Tick(float aDeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* aPlayerInputComponent) override;
	
	FORCEINLINE TObjectPtr<class UInputMappingContext> GetInputMappingContext() { return DefaultMappingContext; }

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ITTInput, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;
};
