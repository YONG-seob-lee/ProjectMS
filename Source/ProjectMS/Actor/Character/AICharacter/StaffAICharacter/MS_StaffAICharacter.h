#pragma once

#include "CoreMinimal.h"
#include "Actor/Character/AICharacter/MS_AICharacter.h"
#include "MathUtility/MS_MathUtility.h"
#include "MS_StaffAICharacter.generated.h"


UCLASS()
class PROJECTMS_API AMS_StaffAICharacter : public AMS_AICharacter
{
	GENERATED_BODY()
	
public:
	AMS_StaffAICharacter();

	virtual void PreInitializeComponents() override;
	virtual void PostInitializeComponents() override;
	
	virtual void BeginPlay() override;
	virtual void Tick(float aDeltaTime) override;


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class UMS_MovingBoxComponent*> MovingBoxComponents;

	UPROPERTY()
	EMS_Direction Direction = EMS_Direction::None;
	
	UPROPERTY(EditAnywhere)
	float DuckVelocity = 5.f;
};
