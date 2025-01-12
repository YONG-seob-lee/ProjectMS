#pragma once

#include "CoreMinimal.h"
#include "AI/AIController/StaffAIController/MS_StaffAIController.h"
#include "MS_CashierStaffAIController.generated.h"

UCLASS() class PROJECTMS_API AMS_CashierStaffAIController : public AMS_StaffAIController
{
	GENERATED_BODY()

public:
	AMS_CashierStaffAIController();

	virtual void OnPossess(APawn* aInPawn) override;
	virtual void OnUnPossess() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type aEndPlayReason) override;

};
