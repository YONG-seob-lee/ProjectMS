#pragma once

#include "CoreMinimal.h"
#include "Actor/Character/MS_CharacterBase.h"
#include "Management/Manager_Both/MS_TableManager.h"
#include "MS_AICharacter.generated.h"

UENUM(BlueprintType) enum class EMS_AIBehaviorPattern : uint8
{
	Undefined		UMETA(DisplayName = "Undefined"),
	Idle			UMETA(DisplayName = "Idle"),
	Observe			UMETA(DisplayName = "Observe"),
	Operate			UMETA(DisplayName = "Operate"),
	Interact		UMETA(DisplayName = "Interact")
};

/* AIBehaviorPattern
* 
*	Observe: Identify the situation and determine the required task
*	Ex: Find empty storage
*
*	Operate: Manipulate the environment or interact with objects
*	Ex: Pick up the items from the storage
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TObjectPtr<class USceneComponent> SceneComponent = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TObjectPtr<class UCapsuleComponent> CollisionCapsuleComponent = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TObjectPtr<class USkeletalMeshComponent> SkeletalMeshComponent = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TObjectPtr<class UCharacterMovementComponent> CharacterMovementComponent = nullptr;
};
