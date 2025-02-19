#pragma once

#include "CoreMinimal.h"
#include "AI/AIController/MS_AIController.h"
#include "MS_StaffAIController.generated.h"

UCLASS()
class PROJECTMS_API AMS_StaffAIController : public AMS_AIController
{
	GENERATED_BODY()
	
public:
	AMS_StaffAIController();

	virtual void Initialize() override;
	virtual void PostInitializeComponents() override;
	virtual void OnPossess(APawn* aInPawn) override;
	virtual void OnUnPossess() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type aEndPlayReason) override;
	
private:	
	UPROPERTY()
	TObjectPtr<class UBehaviorTree> StaffBehaviorTree = nullptr;
	
	UPROPERTY()
	TObjectPtr<class UBlackboardData> StaffBlackboardData = nullptr;
};
