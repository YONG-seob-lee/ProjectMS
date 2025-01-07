#pragma once

#include "CoreMinimal.h"
#include "Actor/Character/AICharacter/MS_AICharacter.h"
#include "MS_StaffAICharacter.generated.h"

UENUM(BlueprintType) enum class EMS_StaffObservePattern : uint8
{
	Undefined			UMETA(DisplayName = "Undefined"),
	Inspection			UMETA(DisplayName = "Inspection")
};

UENUM(BlueprintType) enum class EMS_StaffOperatePattern : uint8
{
	Undefined			UMETA(DisplayName = "Undefined"),
	Move				UMETA(DisplayName = "Move"),
	Fetch				UMETA(DisplayName = "Fetch"),
	Pick				UMETA(DisplayName = "Pick"),
	Drop				UMETA(DisplayName = "Drop"),
};

UENUM(BlueprintType) enum class EMS_StaffInteractPattern : uint8
{
	Undefined			UMETA(DisplayName = "Undefined")
};

UENUM(BlueprintType) enum class EMS_StaffIdlePattern : uint8
{
	Undefined			UMETA(DisplayName = "Undefined")
};

UCLASS() class PROJECTMS_API AMS_StaffAICharacter : public AMS_AICharacter
{
	GENERATED_BODY()
	
public:
	AMS_StaffAICharacter();

	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float aDeltaTime) override;

	UFUNCTION(BlueprintCallable) virtual UClass* GetLoadingStorageType();
	UFUNCTION(BlueprintCallable) virtual UClass* GetUnloadingStorageType();

	// Property
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)int TargetStorageBayOrder = INT_MIN;
};
