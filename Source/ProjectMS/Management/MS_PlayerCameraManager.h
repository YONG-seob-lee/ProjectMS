#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "InputActionValue.h"
#include "Utility/MathUtility/MS_MathUtility.h"
#include "MS_PlayerCameraManager.generated.h"

UENUM() enum class EMS_ViewCameraType
{
	Undefined,
	QuarterView
};

UENUM() enum class EMS_CameraModeType
{
	Undefined,
	FollowingInputCameraMode,
	FollowingPlayerCameraMode,
	ImmobileCameraMode
};

UCLASS() class PROJECTMS_API AMS_PlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

public:
	AMS_PlayerCameraManager();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable) void FadeInCamera(float aDuration, EMS_InterpolationType aInterpolationType);
	UFUNCTION(BlueprintCallable) void FadeOutCamera(float aDuration, EMS_InterpolationType aInterpolationType);
	UFUNCTION(BlueprintCallable) void ZoomCamera(float aMagnification, EMS_InterpolationType aInterpolationType);
	UFUNCTION(BlueprintCallable) void ShakeCamera(float aIntensity, float aDuration);

	FORCEINLINE void SwitchViewCamera(EMS_ViewCameraType aViewCameraType);
	FORCEINLINE void SwitchCameraMode(EMS_CameraModeType aCameraModeType);

	UFUNCTION() void AdjustPostProcessEffect(class UMS_CameraPostProcessEffect* aCameraPostProcessEffect);

	UFUNCTION(BlueprintCallable) void LocateCamera(FVector aLocation);
	UFUNCTION(BlueprintCallable) void RotateCamera(FRotator aRotation);

	UFUNCTION() void DollyIn(const FInputActionValue& aValue);
	UFUNCTION() void DollyOut(const FInputActionValue& aValue);
	UFUNCTION() void TruckLeft(const FInputActionValue& aValue);
	UFUNCTION() void TruckRight(const FInputActionValue& aValue);
	UFUNCTION() void DollyAndTruckOnMobile(FVector2D aPointerGlidePosition, FVector2D aPointerGlidePositionDelta, FVector2D aPointerGlidePositionDeltaTrend);
	UFUNCTION() void PedestalUp(const FInputActionValue& aValue);
	UFUNCTION() void PedestalDown(const FInputActionValue& aValue);
	UFUNCTION() void RollCounterclockwise(const FInputActionValue& aValue);
	UFUNCTION() void RollClockwise(const FInputActionValue& aValue);
	UFUNCTION() void TiltUp(const FInputActionValue& aValue);
	UFUNCTION() void TiltDown(const FInputActionValue& aValue);
	UFUNCTION() void PanLeft(const FInputActionValue& aValue);
	UFUNCTION() void PanRight(const FInputActionValue& aValue);

	UFUNCTION(BlueprintCallable) void GenerateInertiaForce(FVector aMagnitude);

	// Property
private:
	EMS_ViewCameraType ViewCameraType = EMS_ViewCameraType::Undefined;

	float ZoomMagnification = 1.0f;
	FTimerHandle ZoomTimerHandle = {};
	float MoveSensitivity = 1.0f;
	float TurnSensitivity = 1.0f;
	FTimerHandle GenerateInertiaForceTimerHandle = {};
	FVector InertiaForceMagnitude = {};
	bool RestrictedZoneFlag = false;
	FTransform RestrictedZoneTransform = {};
	FVector RestrictedZoneSize = {};

	// Instance
public:
	TObjectPtr<class AMS_ViewCamera> ViewCamera = nullptr;
	TWeakObjectPtr<class UMS_CameraMode> CameraMode = nullptr;
	TObjectPtr<class UMS_CameraEffect> CameraEffect = nullptr;

private:
	TMap<EMS_CameraModeType, TObjectPtr<class UMS_CameraMode>> CameraModeMap = {};
};
