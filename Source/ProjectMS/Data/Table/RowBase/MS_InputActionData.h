#pragma once
    
#include "CoreMinimal.h"
#include "InputAction.h"
#include "MS_InputActionData.generated.h"

UENUM(BlueprintType) enum class EMS_InputActionType : uint8
{
	Undefined,
	MoveForward,
	MoveRear,
	MoveLeft,
	MoveRight,
	DollyIn,
	DollyOut,
	PanLeft,
	PanRight,
	PedestalUp,
	PedestalDown,
	RollClockwise,
	RollCounterclockwise,
	TiltUp,
	TiltDown,
	TruckLeft,
	TruckRight
};

USTRUCT() struct FMS_InputActionData: public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InputData") int32 Index = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InputData") EMS_InputActionType InputActionType = EMS_InputActionType::Undefined;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "InputData") TObjectPtr<class UInputAction> InputAction = nullptr;
};
