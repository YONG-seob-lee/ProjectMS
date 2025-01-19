#pragma once

#include "CoreMinimal.h"
#include "Actor/Character/AICharacter/MS_AICharacter.h"
#include "MS_CustomerAICharacter.generated.h"

UENUM(BlueprintType) enum class EMS_CustomerObservePattern : uint8
{
	Undefined					UMETA(DisplayName = "Undefined"),
	Find						UMETA(DisplayName = "Find")
};

UENUM(BlueprintType) enum class EMS_CustomerOperatePattern : uint8
{
	Undefined					UMETA(DisplayName = "Undefined"),
	MoveToStorage				UMETA(DisplayName = "MoveToStorage"),
	LoadStuff					UMETA(DisplayName = "LoadStuff")
};

UENUM(BlueprintType) enum class EMS_CustomerInteractPattern : uint8
{
	Undefined					UMETA(DisplayName = "Undefined")
};

UENUM(BlueprintType) enum class EMS_CustomerIdlePattern : uint8
{
	Undefined					UMETA(DisplayName = "Undefined")
};

UCLASS() class PROJECTMS_API AMS_CustomerAICharacter : public AMS_AICharacter
{
	GENERATED_BODY()
	
public:
	AMS_CustomerAICharacter();

	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float aDeltaTime) override;

	// Property
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FName CustomerName = NAME_None;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FName Gender = NAME_None;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int Age = INT_MIN;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap<FName, int> WishlistArray = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TMap<FName, int> OrderListArray = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int Money = INT_MIN;

};
