#pragma once

#include "CoreMinimal.h"
#include "Character/MS_CharacterBase.h"
#include "MS_AICharacter.generated.h"


UCLASS()
class PROJECTMS_API AMS_AICharacter : public AMS_CharacterBase
{
	GENERATED_BODY()
	
public:
	AMS_AICharacter();

	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float aDeltaTime) override;
	
	TObjectPtr<class UMS_AIAnimInstance> GetAIAnimInstance() const;
};
