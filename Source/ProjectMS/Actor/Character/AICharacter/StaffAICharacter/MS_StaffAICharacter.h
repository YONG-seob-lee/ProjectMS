#pragma once

#include "CoreMinimal.h"
#include "Character/AICharacter/MS_MarketAICharacter.h"
#include "MS_StaffAICharacter.generated.h"


UCLASS()
class PROJECTMS_API AMS_StaffAICharacter : public AMS_MarketAICharacter
{
	GENERATED_BODY()
	
public:
	AMS_StaffAICharacter();

	void ShowStaffStatusWidget(const FVector2D& _ClickPosition);

	virtual void PreInitializeComponents() override;
	virtual void PostInitializeComponents() override;
	
	virtual void BeginPlay() override;
	virtual void Tick(float aDeltaTime) override;
};
