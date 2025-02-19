#pragma once

#include "CoreMinimal.h"
#include "Character/AICharacter/MS_MarketAICharacter.h"
#include "MS_CustomerAICharacter.generated.h"


UCLASS()
class PROJECTMS_API AMS_CustomerAICharacter : public AMS_MarketAICharacter
{
	GENERATED_BODY()
	
public:
	AMS_CustomerAICharacter();

	virtual void PreInitializeComponents() override;
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float aDeltaTime) override;
};
