#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "InputActionValue.h"
#include "Utility/MathUtility/MS_MathUtility.h"
#include "MS_PlayerCameraManager.generated.h"

#define CAMERA_DISTANCE_STRANGTH 20.0f
#define MAX_CAMERA_DISTANCE 2000.0f
#define MIN_CAMERA_DISTANCE 300.0f

UENUM() enum class EMS_ViewCameraType
{
	Undefined,
	QuarterView,
	SideView
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
	virtual void Destroyed() override;

	// DEBUG
	UFUNCTION(BlueprintCallable) void DEBUGINPUT_OrbitCamera(FVector2D aPointerGlidePosition, FVector2D aPointerGlidePositionDelta, FVector2D aPointerGlidePositionDeltaTrend);
	UFUNCTION() FRotator GenerateInertiaForceForRotation(FRotator aCurrentRotation, FRotator aTargetRotation, float& aVelocity, float aDampingFactor);

	UFUNCTION(BlueprintCallable) void FadeInCamera(float aDuration, EMS_InterpolationType aInterpolationType);
	UFUNCTION(BlueprintCallable) void FadeOutCamera(float aDuration, EMS_InterpolationType aInterpolationType);
	UFUNCTION(BlueprintCallable) void ZoomCamera(float aDistance);
	UFUNCTION(BlueprintCallable) void OrbitCamera(float aFloat);
	UFUNCTION(BlueprintCallable) void ShakeCamera(float aIntensity, float aDuration);

	UFUNCTION(BlueprintCallable) void InitializeViewCamera();
	FORCEINLINE void SwitchViewCamera(EMS_ViewCameraType aViewCameraType, FViewTargetTransitionParams aTransitionParam = FViewTargetTransitionParams());
	FORCEINLINE void SwitchCameraMode(EMS_CameraModeType aCameraModeType);

	UFUNCTION() void AdjustPostProcessEffect(class UMS_CameraPostProcessEffect* aCameraPostProcessEffect);

	void LocateAndRotateCamera(const FVector& aLocation, const FRotator& aRotation, EMS_ViewCameraType aViewCameraType = EMS_ViewCameraType::QuarterView);
	
	UFUNCTION(BlueprintCallable) void LocateCamera(FVector aLocation);
	UFUNCTION(BlueprintCallable) void RotateCamera(FRotator aRotation);

	UFUNCTION() void DollyIn(const FInputActionValue& aValue);
	UFUNCTION() void DollyOut(const FInputActionValue& aValue);
	UFUNCTION() void TruckLeft(const FInputActionValue& aValue);
	UFUNCTION() void TruckRight(const FInputActionValue& aValue);
	UFUNCTION() void DollyAndTruck(FVector2D aPointerGlidePosition, FVector2D aPointerGlidePositionDelta, FVector2D aPointerGlidePositionDeltaTrend);
	UFUNCTION() void PedestalUp(const FInputActionValue& aValue);
	UFUNCTION() void PedestalDown(const FInputActionValue& aValue);
	UFUNCTION() void RollCounterclockwise(const FInputActionValue& aValue);
	UFUNCTION() void RollClockwise(const FInputActionValue& aValue);
	UFUNCTION() void TiltUp(const FInputActionValue& aValue);
	UFUNCTION() void TiltDown(const FInputActionValue& aValue);
	UFUNCTION() void PanLeft(const FInputActionValue& aValue);
	UFUNCTION() void PanRight(const FInputActionValue& aValue);

	UFUNCTION(BlueprintCallable) void GenerateInertiaForce(FVector aMagnitude);
	
	FORCEINLINE FSimpleDelegate& GetOnFinishedCameraTransitionDelegate() { return OnFinishedCameraTransition; }

	// Property
private:
	EMS_ViewCameraType ViewCameraType = EMS_ViewCameraType::Undefined;

	float ZoomMagnification = 1.0f;
	FTimerHandle ZoomTimerHandle = {};
	float MoveSensitivity = 1.0f;
	float TurnSensitivity = 1.0f;
	FTimerHandle GenerateInertiaForceTimerHandle = {};
	FVector InertiaForceMagnitude = {};

	float CameraInertiaForce = 0.0f;
	FTimerHandle CameraInertiaTimerHandle = {};

	FTimerHandle CameraTransitionTimerHandle = {};
	FSimpleDelegate OnFinishedCameraTransition = {};
	// DEBUG
	FTimerHandle CameraRotationTimerHandle = {};
	FRotator TargetCameraRotation = {};

	// Instance
public:
	TWeakObjectPtr<class AMS_ViewCamera> ViewCamera = nullptr;
	TWeakObjectPtr<class UMS_CameraMode> CameraMode = nullptr;
	TObjectPtr<class UMS_CameraEffect> CameraEffect = nullptr;

	inline static TObjectPtr<AMS_PlayerCameraManager> CameraManager = nullptr;
	static AMS_PlayerCameraManager* GetInstance();

private:
	TMap<EMS_CameraModeType, TObjectPtr<class UMS_CameraMode>> CameraModeMap = {};
	TMap<EMS_ViewCameraType, TObjectPtr<class AMS_ViewCamera>> ViewCameraMap = {};
	
#define gCameraMng (*AMS_PlayerCameraManager::GetInstance())
};