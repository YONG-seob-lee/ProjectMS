#pragma once

#include "CoreMinimal.h"
#include "Unit/UnitState/MS_UnitStateBase.h"
#include "MS_PlayerUnitState.generated.h"

UCLASS() class PROJECTMS_API UMS_PlayerUnitState : public UMS_UnitStateBase
{
	GENERATED_BODY()
	
public:
	UMS_PlayerUnitState();

	virtual void WeakBindController(const TObjectPtr<class AMS_PlayerController>& aPlayerController) override;

	// Instance
public:
	UPROPERTY() TObjectPtr<class UMS_UnitInputHandler> UnitInputHandler = nullptr;
};
