#pragma once

#include "CoreMinimal.h"
#include "CoreClass/StateMachine/MS_StateBase.h"
#include "MS_UnitStateBase.generated.h"

UCLASS()
class PROJECTMS_API UMS_UnitStateBase : public UMS_StateBase
{
	GENERATED_BODY()

public:
	UMS_UnitStateBase();

	void SetupPlayerInputComponent(class UInputComponent* aPlayerInputComponent);
	virtual void WeakBindController(const TObjectPtr<class AMS_PlayerController>& aPlayerController);

	// Instance
protected:
	UPROPERTY() TWeakObjectPtr<class AMS_PlayerController> PlayerController = nullptr;
};
