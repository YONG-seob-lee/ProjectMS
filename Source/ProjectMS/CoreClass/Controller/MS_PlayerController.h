#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "ProjectMS/Management/MS_Management.h"
#include "ProjectMS/Unit/MS_UnitBase.h"
#include "MS_PlayerController.generated.h"

#define POINTER_HOLD_DELAY 0.35f
#define POINTER_CLICK_DELAY 0.25f
#define POINTER_DOUBLE_CLICK_DELAY 0.25f
#define POINTER_DOUBLE_CLICK_POSITION_TOLERANCE 5.0f

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FXOnPointerDownDelegate, FVector2D, aPointerDownPosition, AActor*, aPointerDownActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FXOnPointerUpDelegate, FVector2D, aPointerUpPosition, AActor*, aPointerUpActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FXOnPointerMoveDelegate, FVector2D, aPointerMovePosition, FVector2D, aPointerMovePositionDelta, FVector2D, aPointerMovePositionDeltaTrend);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FXOnPointerGlideDelegate, FVector2D, aPointerGlidePosition, FVector2D, aPointerGlidePositionDelta, FVector2D, aPointerGlidePositionDeltaTrend);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FXOnPointerHoldDelegate, FVector2D, aPointerHoldPosition, AActor*, aPointerHoldActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FXOnPointerHeldDelegate, FVector2D, aPointerHeldPosition, AActor*, aPointerHeldActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FXOnPointerClickDelegate, FVector2D, aPointerClickPosition, AActor*, aPointerClickActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FXOnPinchActionDelegate, float, aPinchValue);

UCLASS() class PROJECTMS_API AMS_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMS_PlayerController();
	virtual void PostLoad() override;
	virtual void Tick(float aDeltaTime) override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);
	virtual void SetupInputComponent() override;

public:
	void RegisterManagement();

	TObjectPtr<class AMS_CharacterBase> GetCharacterBase() const;
	TObjectPtr<class UMS_TableManager> GetTableManager() const;
	TObjectPtr<class UMS_UnitManager> GetUnitManager() const;
	TObjectPtr<class AMS_SceneManager> GetSceneManager() const;
	TObjectPtr<class UMS_WidgetManager> GetWidgetManager() const;
	FORCEINLINE class UInputMappingContext* GetInputMappingContext() { return MappingContext; }

private:
	UPROPERTY() TObjectPtr<UMS_UnitBase> UnitBase = nullptr;
	UPROPERTY() TObjectPtr<UMS_Management> Management = nullptr;

/* Input */
public:
	FORCEINLINE FVector2D AcquirePointerPositionOnViewport();

	UFUNCTION() void HandlePointerDown(const FInputActionValue& aValue);
	UFUNCTION() void HandlePointerUp(const FInputActionValue& aValue);
	UFUNCTION() void HandlePointerHold();
	UFUNCTION() void HandlePointerClick();
	UFUNCTION() void HandlePointerMove();
	UFUNCTION() void HandlePointerGlide();

	UFUNCTION() void HandlePinchAction(const FInputActionValue& aValue);

	// Property
private:
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
	UPROPERTY() AActor* PointerHeldActor = nullptr;

	UPROPERTY() int64 PointerClickTimestamp = 0;
	UPROPERTY() FVector2D PointerClickPosition = { -FLT_MAX, -FLT_MAX };
	UPROPERTY() AActor* PointerClickActor = nullptr;
	UPROPERTY() float PointerClickIntervalTime = -FLT_MAX;

	// Instance
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true")) class UInputMappingContext* MappingContext = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true")) TObjectPtr<class UInputAction> PinchInputAction = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true")) TObjectPtr<class UInputAction> PointerPressInputAction = nullptr;

	// Delegate
public:
	FXOnPointerDownDelegate OnPointerDownDelegate = {};
	FXOnPointerUpDelegate OnPointerUpDelegate = {};
	FXOnPointerMoveDelegate OnPointerMoveDelegate = {};
	FXOnPointerHoldDelegate OnPointerHoldDelegate = {};
	FXOnPointerClickDelegate OnPointerClickDelegate = {};
	FXOnPointerHeldDelegate OnPointerHeldDelegate = {};
	FXOnPointerGlideDelegate OnPointerGlideDelegate = {};

	FXOnPinchActionDelegate OnPinchActionDelegate = {};
};