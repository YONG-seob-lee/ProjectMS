#pragma once

#include "CoreMinimal.h"
#include "Actor/Character/AICharacter/MS_AICharacter.h"
#include "MS_CustomerAICharacter.generated.h"

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

};
