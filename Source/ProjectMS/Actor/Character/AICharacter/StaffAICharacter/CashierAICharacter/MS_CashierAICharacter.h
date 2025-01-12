#pragma once

#include "CoreMinimal.h"
#include "Actor/Character/AICharacter/StaffAICharacter/MS_StaffAICharacter.h"
#include "MS_CashierAICharacter.generated.h"

UCLASS() class PROJECTMS_API AMS_CashierAICharacter : public AMS_StaffAICharacter
{
	GENERATED_BODY()
	
public:
	AMS_CashierAICharacter();

	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float aDeltaTime) override;
};
