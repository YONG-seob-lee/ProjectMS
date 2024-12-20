

#pragma once

#include "CoreMinimal.h"
#include "MS_ModeStateBase.h"
#include "MS_ModeState_Construct.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_ModeState_Construct : public UMS_ModeStateBase
{
	GENERATED_BODY()
	
public:
	UMS_ModeState_Construct();

	virtual void Initialize(uint8 aIndex, const FName& aName) override;
	virtual void Finalize() override;

	virtual void Tick(float aDeltaTime) override;
	
protected:
	virtual void Begin() override;
	virtual void Exit() override;

public:
	virtual void OnInputPointerDown() override;
	virtual void OnInputPointerUp() override;
	virtual void OnInputPointerMove() override;
	virtual void OnInputPointerHold() override;
	virtual void OnInputPointerClick() override;
	virtual void OnInputPointerGlide() override;


protected:
	TObjectPtr<class AMS_Preview> PreviewObject;
};
