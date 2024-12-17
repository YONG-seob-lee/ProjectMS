#pragma once

#include "CoreMinimal.h"
#include "Actor/Character/AICharacter/MS_AICharacter.h"
#include "MS_StaffAICharacter.generated.h"

UENUM(BlueprintType) enum class EMS_StaffAIObservePattern : uint8
{
	Undefined			UMETA(DisplayName = "Undefined"),
	Inspection			UMETA(DisplayName = "Inspection")
};

UENUM(BlueprintType) enum class EMS_StaffAIOperatePattern : uint8
{
	Undefined			UMETA(DisplayName = "Undefined"),
	Fetch				UMETA(DisplayName = "Fetch"),
	Pick				UMETA(DisplayName = "Pick"),
	Drop				UMETA(DisplayName = "Drop"),
};


UCLASS() class PROJECTMS_API AMS_StaffAICharacter : public AMS_AICharacter
{
	GENERATED_BODY()
	
public:
	AMS_StaffAICharacter();

	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float aDeltaTime) override;

	// Property
public:
	EMS_StaffAIObservePattern StaffAIObservePattern = EMS_StaffAIObservePattern::Undefined;
	EMS_StaffAIOperatePattern StaffAIOperatePattern = EMS_StaffAIOperatePattern::Undefined;
};
