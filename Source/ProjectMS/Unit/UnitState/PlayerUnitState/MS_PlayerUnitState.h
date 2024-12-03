#pragma once

#include "CoreMinimal.h"
#include "Unit/UnitState/MS_UnitStateBase.h"
#include "MS_PlayerUnitState.generated.h"

UCLASS() class PROJECTMS_API UMS_PlayerUnitState : public UMS_UnitStateBase
{
	GENERATED_BODY()
	
public:
	UMS_PlayerUnitState();

	// Instance
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (AllowPrivateAccess = "true")) TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY() TObjectPtr<class UMS_UnitInputHandler> UnitInputHandler = nullptr;
};
