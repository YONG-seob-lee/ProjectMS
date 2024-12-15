#pragma once

#include "CoreMinimal.h"
#include "Actor/Character/MS_CharacterBase.h"
#include "MS_AICharacter.generated.h"

UCLASS() class PROJECTMS_API AMS_AICharacter : public AMS_CharacterBase
{
	GENERATED_BODY()
	
public:
	AMS_AICharacter();

	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float aDeltaTime) override;

	// Component
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) class USceneComponent* SceneComponent = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) class UCapsuleComponent* CollisionCapsuleComponent = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) class USkeletalMeshComponent* SkeletalMeshComponent = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) class UCharacterMovementComponent* CharacterMovementComponent = nullptr;
};
