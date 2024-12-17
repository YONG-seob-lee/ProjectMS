#pragma once

#include "CoreMinimal.h"
#include "Actor/Character/MS_CharacterBase.h"
#include "MS_AICharacter.generated.h"

UENUM(BlueprintType) enum class EMS_AIBehaviorPattern : uint8
{
	Undefined		UMETA(DisplayName = "Undefined"),
	Navigate		UMETA(DisplayName = "Navigate"),
	Operate			UMETA(DisplayName = "Operate"),
	Observe			UMETA(DisplayName = "Observe"),
	Interact		UMETA(DisplayName = "Operate"),
	Idle			UMETA(DisplayName = "Idle")
};

/* AIBehaviorPattern
* 
*	Navigate: Move to location
*
*	Operate: Manipulate the environment or interact with objects
*	Ex: Pick up the items from the storage
* 
*	Observe: Identify the situation and determine the required task
*	Ex: Find empty storage
* 
*	Interact: Tasks that interact with other AIs or objects
*	Ex: Payment, cooperation, conversation with customers.
* 
*	Idle : Idle
*/

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

	// Property
public:
	EMS_AIBehaviorPattern AIBehaviorPattern = EMS_AIBehaviorPattern::Undefined;
};
