#pragma once

#include "CoreMinimal.h"
#include "Actor/MS_Actor.h"
#include "Actor/Character/AICharacter/CustomerAICharacter/MS_CustomerAICharacter.h"
#include "MS_CustomerSuperviseActor.generated.h"

UENUM(BlueprintType) enum class EMS_AISuperviseType : uint8
{
	Undefined			UMETA(DisplayName = "Undefined"),
	Enter				UMETA(DisplayName = "Enter"),
	Exit				UMETA(DisplayName = "Exit")
};

USTRUCT(BlueprintType) struct FMS_CustomerSpawnParameters
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName CustomerName = NAME_None;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Gender = NAME_None;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Age = INT_MIN;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, int32> WishlistArray = {};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RandomStuffSelectionFactor = 0.0f;
};

UCLASS() class PROJECTMS_API AMS_CustomerSuperviseActor : public AMS_Actor
{
	GENERATED_BODY()
	
public:
	AMS_CustomerSuperviseActor(const FObjectInitializer& aObjectInitializer);

protected:
	virtual void BeginPlay() override;

	
public:
	UFUNCTION(BlueprintCallable)
	void SpawnCustomerCharacter(const FMS_CustomerSpawnParameters& aSpawnParams);
	
	UFUNCTION(BlueprintCallable)
	void DestroyCustomerCharacter(class AMS_CustomerAICharacter* aCharacter);

	// Component
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class USceneComponent> SceneComponent = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UBoxComponent> BoxComponent = nullptr;

	// Property
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EMS_AISuperviseType SuperviseType = EMS_AISuperviseType::Undefined;
};
