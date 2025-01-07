#pragma once

#include "CoreMinimal.h"
#include "Actor/Character/MS_CharacterBase.h"
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

USTRUCT(BlueprintType) struct FMS_PositiveEmotionGroup
{
	GENERATED_BODY()

public:
	int Happiness = INT_MIN;
	int Passion = INT_MIN;
	int Confidence = INT_MIN;
	int Inspiration = INT_MIN;
	int Gratitude = INT_MIN;
};

USTRUCT(BlueprintType) struct FMS_NagativeEmotionGroup
{
	GENERATED_BODY()

public:
	int Stress = INT_MIN;
	int Anxiety = INT_MIN;
	int Boredom = INT_MIN;
	int Anger = INT_MIN;
	int Helplessness = INT_MIN;
};

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

	// Properties
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FMS_PositiveEmotionGroup PositiveEmotionGroup = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FMS_NagativeEmotionGroup NagativeEmotionGroup = {};
};
