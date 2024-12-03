#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MS_UnitInputHandler.generated.h"

#define POINTER_HOLD_DELAY 0.35f
#define POINTER_CLICK_DELAY 0.25f
#define POINTER_DOUBLE_CLICK_DELAY 0.25f

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FXOnPointerDownDelegate, FVector2D, aPointerDownPosition, AActor*, aPointerDownActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FXOnPointerUpDelegate, FVector2D, aPointerUpPosition, AActor*, aPointerUpActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FXOnPointerMoveDelegate, FVector2D, aPointerMovePosition, FVector2D, aPointerMovePositionDelta, FVector2D, aPointerMovePositionDeltaTrend);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FXOnPointerHoverEnterDelegate, FVector2D, aPointerHoverEnterPosition, AActor*, aPointerHoverActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FXOnPointerHoverDelegate, FVector2D, aPointerHoverPosition, AActor*, aPointerHoverActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FXOnPointerHoverLeaveDelegate, FVector2D, aPointerHoverLeavePosition, AActor*, aPointerHoverActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FXOnPointerGlideDelegate, FVector2D, aPointerGlidePosition, FVector2D, aPointerGlidePositionDelta, FVector2D, aPointerGlidePositionDeltaTrend);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FXOnPointerDragDelegate, FVector2D, aPointerDragStartPosition, FVector2D, aPointerDragEndPosition, const TArray<AActor*>&, aPointerDragActorArray);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FXOnPointerHoldDelegate, FVector2D, aPointerHoldPosition, AActor*, aPointerHoldActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FXOnPointerClickDelegate, FVector2D, aPointerClickPosition, AActor*, aPointerClickActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FXOnPointerDoubleClickDelegate, FVector2D, aPointerDoubleClickPosition, AActor*, aPointerDoubleClickActor);

UCLASS() class PROJECTMS_API UMS_UnitInputHandler : public UObject
{
	GENERATED_BODY()
	
public:
	UMS_UnitInputHandler();

	UFUNCTION() void BindController(class AMS_PlayerController* aPlayerController);

protected:
	UFUNCTION() void HandleMouseLeftButtonDown();
	UFUNCTION() void HandleMouseLeftButtonUp();
	UFUNCTION() void HandleMouseRightButtonDown();
	UFUNCTION() void HandleMouseRightButtonUp();
	UFUNCTION() void HandleTouchDown(ETouchIndex::Type aFingerIndex, FVector aLocation);
	UFUNCTION() void HandleTouchUp(ETouchIndex::Type aFingerIndex, FVector aLocation);

	UFUNCTION() void HandlePointerDown();
	UFUNCTION() void HandlePointerUp();
	UFUNCTION() void HandlePointerMove();
	UFUNCTION() void HandlePointerHover();
	UFUNCTION() void HandlePointerGlide();
	UFUNCTION() void HandlePointerDrag();
	UFUNCTION() void HandlePointerHold();
	UFUNCTION() void HandlePointerClick();
	UFUNCTION() void HandlePointerDoubleClick();

	// Property
public:
	UPROPERTY() bool MouseLeftButtonPressFlag = false;
	UPROPERTY() bool MouseRightButtonPressFlag = false;
	UPROPERTY() bool TouchPressFlag = false;

	UPROPERTY() int64 PointerDownTimestamp = 0;
	UPROPERTY() FVector2D PointerDownPosition = { -FLT_MAX, -FLT_MAX };
	UPROPERTY() AActor* PointerDownActor = nullptr;
	UPROPERTY() int64 PointerUpTimestamp = 0;
	UPROPERTY() FVector2D PointerUpPosition = { -FLT_MAX, -FLT_MAX };
	UPROPERTY() AActor* PointerUpActor = nullptr;
	UPROPERTY() float PointerDownUpIntervalTime = -FLT_MAX;

	FTimerHandle HandlePointerMoveTimerHandle = {};
	UPROPERTY() FVector2D PointerMovePosition = { -FLT_MAX, -FLT_MAX };
	UPROPERTY() FVector2D PointerMovePositionDelta = { -FLT_MAX, -FLT_MAX };
	UPROPERTY() TArray<FVector2D> PointerMovePositionDeltaArray = {};
	UPROPERTY() FVector2D PointerMovePositionDeltaTrend = { -FLT_MAX, -FLT_MAX };

	FTimerHandle HandlePointerHoverTimerHandle = {};
	UPROPERTY() FVector2D PointerHoverPosition = { -FLT_MAX, -FLT_MAX };
	UPROPERTY() AActor* PointerHoverActor = nullptr;

	UPROPERTY() FVector2D PointerGlidePosition = { -FLT_MAX, -FLT_MAX };
	UPROPERTY() FVector2D PointerGlidePositionDelta = { -FLT_MAX, -FLT_MAX };
	UPROPERTY() TArray<FVector2D> PointerGlidePositionDeltaArray = {};
	UPROPERTY() FVector2D PointerGlidePositionDeltaTrend = { -FLT_MAX, -FLT_MAX };

	FTimerHandle HandlePointerDragTimerHandle = {};
	UPROPERTY() bool PointerDragFlag = false;
	UPROPERTY() FVector2D PointerDragStartPosition = { -FLT_MAX, -FLT_MAX };
	UPROPERTY() FVector2D PointerDragEndPosition = { -FLT_MAX, -FLT_MAX };
	UPROPERTY() TArray<AActor*> PointerDragActorArray = {};

	FTimerHandle HandlePointerHoldTimerHandle = {};
	UPROPERTY() FVector2D PointerHoldPosition = { -FLT_MAX, -FLT_MAX };
	UPROPERTY() AActor* PointerHoldActor = nullptr;

	UPROPERTY() int64 PointerClickTimestamp = 0;
	UPROPERTY() FVector2D PointerClickPosition = { -FLT_MAX, -FLT_MAX };
	UPROPERTY() AActor* PointerClickActor = nullptr;
	UPROPERTY() float PointerClickIntervalTime = -FLT_MAX;

	UPROPERTY() FVector2D PointerDoubleClickPosition = { -FLT_MAX, -FLT_MAX };
	UPROPERTY() AActor* PointerDoubleClickActor = nullptr;

	// Instance
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TObjectPtr<class AMS_PlayerController> PlayerControllerInst = nullptr;

	// Delegate
public:
	FXOnPointerDownDelegate OnPointerDownDelegate = {};
	FXOnPointerUpDelegate OnPointerUpDelegate = {};
	FXOnPointerMoveDelegate OnPointerMoveDelegate = {};
	FXOnPointerHoverEnterDelegate OnPointerHoverEnterDelegate = {};
	FXOnPointerHoverDelegate OnPointerHoverDelegate = {};
	FXOnPointerHoverLeaveDelegate OnPointerHoverLeaveDelegate = {};
	FXOnPointerGlideDelegate OnPointerGlideDelegate = {};
	FXOnPointerDragDelegate OnPointerDragDelegate = {};
	FXOnPointerHoldDelegate OnPointerHoldDelegate = {};
	FXOnPointerClickDelegate OnPointerClickDelegate = {};
	FXOnPointerDoubleClickDelegate OnPointerDoubleClickDelegate = {};
};
