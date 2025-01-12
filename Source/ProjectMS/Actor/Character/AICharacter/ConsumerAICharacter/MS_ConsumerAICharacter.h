#pragma once

#include "CoreMinimal.h"
#include "Actor/Character/AICharacter/MS_AICharacter.h"
#include "MS_ConsumerAICharacter.generated.h"

UCLASS() class PROJECTMS_API AMS_ConsumerAICharacter : public AMS_AICharacter
{
	GENERATED_BODY()
	
public:
	AMS_ConsumerAICharacter();

	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float aDeltaTime) override;
};
