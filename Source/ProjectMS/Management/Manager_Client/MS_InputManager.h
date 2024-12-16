// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "MS_ManagerBase.h"
#include "MS_InputManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FXOnPointerDownDelegate, FVector2D, aPointerDownPosition, AActor*, aPointerDownActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FXOnPointerUpDelegate, FVector2D, aPointerUpPosition, AActor*, aPointerUpActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FXOnPointerMoveDelegate, FVector2D, aPointerMovePosition, FVector2D, aPointerMovePositionDelta, FVector2D, aPointerMovePositionDeltaTrend);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FXOnPointerGlideDelegate, FVector2D, aPointerGlidePosition, FVector2D, aPointerGlidePositionDelta, FVector2D, aPointerGlidePositionDeltaTrend);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FXOnMouseRightButtonGlideDelegate, FVector2D, aPointerGlidePosition, FVector2D, aPointerGlidePositionDelta, FVector2D, aPointerGlidePositionDeltaTrend);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FXOnPointerHoldDelegate, FVector2D, aPointerHoldPosition, AActor*, aPointerHoldActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FXOnPointerClickDelegate, FVector2D, aPointerClickPosition, AActor*, aPointerClickActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FXOnPinchActionDelegate, float, aPinchValue);
/**
 * 
 */
UCLASS()
class PROJECTMS_API UMS_InputManager : public UMS_ManagerBase
{
	GENERATED_BODY()
public:
	UMS_InputManager();

	virtual void Initialize() override;
	virtual void Finalize() override;

	void SetupInputComponent(const TObjectPtr<UInputComponent>& aInputComponent, const TObjectPtr<ULocalPlayer>& aLocalPlayer);
	
/* Input */
public:
	FORCEINLINE FVector2D AcquirePointerPositionOnViewport() const;

	UFUNCTION() void HandlePointerDown(const FInputActionValue& aValue);
	UFUNCTION() void HandlePointerUp(const FInputActionValue& aValue);
	UFUNCTION() void HandlePointerHold();
	UFUNCTION() void HandlePointerClick();
	UFUNCTION() void HandlePointerMove();
	UFUNCTION() void HandlePointerGlide();

	UFUNCTION() void HandlePinchAction(const FInputActionValue& aValue);

	// DEBUG
	UFUNCTION() void HandleMouseRightButtonDown(const FInputActionValue& aValue);
	UFUNCTION() void HandleMouseRightButtonUp(const FInputActionValue& aValue);

	// Property
private:
	
	bool GetHitResultUnderCursor(ECollisionChannel TraceChannel, bool bTraceComplex, FHitResult& HitResult) const;
	
	UPROPERTY() bool PointerPressFlag = false;

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

	UPROPERTY() FVector2D PointerGlidePosition = { -FLT_MAX, -FLT_MAX };
	UPROPERTY() FVector2D PointerGlidePositionDelta = { -FLT_MAX, -FLT_MAX };
	UPROPERTY() TArray<FVector2D> PointerGlidePositionDeltaArray = {};
	UPROPERTY() FVector2D PointerGlidePositionDeltaTrend = { -FLT_MAX, -FLT_MAX };

	FTimerHandle HandlePointerHoldTimerHandle = {};
	UPROPERTY() FVector2D PointerHoldPosition = { -FLT_MAX, -FLT_MAX };
	UPROPERTY() AActor* PointerHoldActor = nullptr;

	UPROPERTY() int64 PointerClickTimestamp = 0;
	UPROPERTY() FVector2D PointerClickPosition = { -FLT_MAX, -FLT_MAX };
	UPROPERTY() AActor* PointerClickActor = nullptr;
	UPROPERTY() float PointerClickIntervalTime = -FLT_MAX;

	// DEBUG
	UPROPERTY() bool MouseRightButtonPressFlag = false;

	// Instance
private:

	// Delegate
public:
	FXOnPointerDownDelegate OnPointerDownDelegate = {};
	FXOnPointerUpDelegate OnPointerUpDelegate = {};
	FXOnPointerMoveDelegate OnPointerMoveDelegate = {};
	FXOnPointerHoldDelegate OnPointerHoldDelegate = {};
	FXOnPointerClickDelegate OnPointerClickDelegate = {};
	FXOnPointerGlideDelegate OnPointerGlideDelegate = {};

	FXOnPinchActionDelegate OnPinchActionDelegate = {};

	// DEBUG
	FXOnMouseRightButtonGlideDelegate OnMouseRightButtonGlideDelegate = {};

	UPROPERTY()
	class UInputMappingContext* MappingContext = nullptr;
	UPROPERTY()
	TObjectPtr<class UInputAction> PinchInputAction = nullptr;
	UPROPERTY()
	TObjectPtr<class UInputAction> RotationInputAction = nullptr;
	UPROPERTY()
	TObjectPtr<class UInputAction> PointerPressInputAction = nullptr;
	
public:
	inline static TObjectPtr<UMS_InputManager> InputManager = nullptr;
	static UMS_InputManager* GetInstance();
	
#define gInputMng (*UMS_InputManager::GetInstance())
};
