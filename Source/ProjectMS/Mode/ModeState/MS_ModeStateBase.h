

#pragma once

#include "CoreMinimal.h"
#include "StateMachine/MS_StateBase.h"
#include "MS_ModeStateBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_ModeStateBase : public UMS_StateBase
{
	GENERATED_BODY()
	
public:
	UMS_ModeStateBase();

	virtual void Initialize(uint8 aIndex, const FName& aName) override;
	virtual void Finalize() override;

	virtual void Tick(float aDeltaTime) override;
	
protected:
	virtual void Begin() override;
	virtual void Exit() override;

public:
	virtual void OnInputPointerDown();
	virtual void OnInputPointerUp();
	virtual void OnInputPointerMove();
	virtual void OnInputPointerHold();
	virtual void OnInputPointerClick();
	virtual void OnInputPointerGlide();
};
